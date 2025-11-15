#include "events_cmd.hh"

namespace dockercpp::command {

EventsCmdImpl::EventsCmdImpl(std::unique_ptr<events::Exec> exec)
    : AbstrDockerCmd<EventsCmd, std::vector<DockerEvent>>(std::move(exec)) {}

std::vector<DockerEvent> EventsCmdImpl::exec() {
    return m_execution->exec(shared_from_this());
}

std::vector<std::string> EventsCmdImpl::getFilters() const {
    std::vector<std::string> result;
    for (const auto& [key, values] : m_filters) {
        for (const auto& value : values) {
            result.push_back(key + "=" + value);
        }
    }
    return result;
}

}
