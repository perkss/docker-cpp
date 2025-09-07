#include "events_cmd_exec.hh"

#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

EventsCmdExec::EventsCmdExec()
    : AbstrSyncDockerCmdExec<EventsCmd, std::vector<DockerEvent>>(),
      events::Exec() {}

std::vector<DockerEvent> EventsCmdExec::exec(std::shared_ptr<EventsCmd> command) {
    return execute(command);
}

void EventsCmdExec::from_json(const nlohmann::json& j, DockerEvent& event) {
    event.type = j.value("Type", "");
    event.action = j.value("Action", "");
    event.id = j.value("id", "");
    event.from = j.value("from", "");
    event.time = j.value("time", 0);
    event.timeNano = j.value("timeNano", 0);
    event.status = j.value("status", "");
    event.scope = j.value("scope", "");
    
    if (j.contains("Actor") && j["Actor"].is_object()) {
        const auto& actor = j["Actor"];
        event.actor.id = actor.value("ID", "");
        
        auto attrs = actor.value("Attributes", nlohmann::json::object());
        for (auto it = attrs.begin(); it != attrs.end(); ++it) {
            event.actor.attributes[it.key()] = it.value().get<std::string>();
        }
    }

    if (j.contains("Labels") && j["Labels"].is_object()) {
        const auto& labels = j["Labels"];
        for (auto it = labels.begin(); it != labels.end(); ++it) {
            event.labels[it.key()] = it.value().get<std::string>();
        }
    }
}

nlohmann::json EventsCmdExec::buildFilterJson(const std::vector<std::string>& filters) {
    nlohmann::json filterJson = nlohmann::json::object();
    for (const auto& filter : filters) {
        size_t pos = filter.find('=');
        if (pos != std::string::npos) {
            std::string key = filter.substr(0, pos);
            std::string value = filter.substr(pos + 1);
            if (!filterJson.contains(key)) {
                filterJson[key] = nlohmann::json::array();
            }
            filterJson[key].push_back(value);
        }
    }
    return filterJson;
}

std::vector<DockerEvent> EventsCmdExec::execute(std::shared_ptr<EventsCmd> command) {
    core::WebTarget webResource = m_webTarget->path("events");

    // Add query parameters
    if (command->getSince() > 0) {
        webResource = webResource.queryParam("since", std::to_string(command->getSince()));
    }
    if (command->getUntil() > 0) {
        webResource = webResource.queryParam("until", std::to_string(command->getUntil()));
    }

    // Add filters
    auto filters = command->getFilters();
    if (!filters.empty()) {
        nlohmann::json filterJson = buildFilterJson(filters);
        webResource = webResource.queryParam("filters", filterJson.dump());
    }

    auto response = webResource.request().get();
    std::vector<DockerEvent> events;

    // Docker events come as newline-delimited JSON
    std::istringstream stream(response);
    std::string line;
    while (std::getline(stream, line)) {
        if (line.empty()) continue;

        try {
            const nlohmann::json json = nlohmann::json::parse(line);
            DockerEvent event;
            from_json(json, event);
            events.push_back(event);
        } catch (const nlohmann::json::exception& e) {
            spdlog::error("Failed to parse event JSON: {}", e.what());
            continue;
        }
    }

    return events;
}

}  // namespace dockercpp::command::exec
