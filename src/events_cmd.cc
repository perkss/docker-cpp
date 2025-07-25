#include "events_cmd.hh"

namespace dockercpp::command {

EventsCmdImpl::EventsCmdImpl(std::unique_ptr<events::Exec> exec)
    : AbstrDockerCmd<EventsCmd, std::vector<DockerEvent>>(std::move(exec)),
      m_since(0),
      m_until(0) {}

std::vector<DockerEvent> EventsCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

int64_t EventsCmdImpl::getSince() const {
    return m_since;
}

int64_t EventsCmdImpl::getUntil() const {
    return m_until;
}

EventsCmd& EventsCmdImpl::withSince(int64_t since) {
    m_since = since;
    return *this;
}

EventsCmd& EventsCmdImpl::withUntil(int64_t until) {
    m_until = until;
    return *this;
}

}
