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

std::vector<DockerEvent> EventsCmdExec::execute(std::shared_ptr<EventsCmd> command) {
    core::WebTarget webResource = m_webTarget->path("events");

    // Add query parameters
    if (command->getSince() > 0) {
        webResource = webResource.queryParam("since", std::to_string(command->getSince()));
    }
    if (command->getUntil() > 0) {
        webResource = webResource.queryParam("until", std::to_string(command->getUntil()));
    }

    auto response = webResource.request().get();

    spdlog::info("converting string {}", response);

    const nlohmann::json json = nlohmann::json::parse(response);
    std::vector<DockerEvent> events;

    for (const auto& event : json) {
        DockerEvent dockerEvent;
        dockerEvent.type = event.value("Type", "");
        dockerEvent.action = event.value("Action", "");
        dockerEvent.id = event.value("id", "");
        dockerEvent.from = event.value("from", "");
        dockerEvent.time = event.value("time", 0);
        dockerEvent.timeNano = event.value("timeNano", 0);
        dockerEvent.actor = event.value("Actor", nlohmann::json::object());
        events.push_back(dockerEvent);
    }

    return events;
}

}  // namespace dockercpp::command::exec
