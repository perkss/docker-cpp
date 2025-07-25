#include "stats_container_cmd.hh"

namespace dockercpp::command {

StatsContainerCmdImpl::StatsContainerCmdImpl(std::unique_ptr<stats::Exec> exec)
    : AbstrDockerCmd<StatsContainerCmd, std::vector<Stats>>(std::move(exec)),
      m_noStream(false) {}

std::vector<Stats> StatsContainerCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

std::string StatsContainerCmdImpl::getContainerId() const {
    return m_containerId;
}

StatsContainerCmd& StatsContainerCmdImpl::withContainerId(const std::string& id) {
    m_containerId = id;
    return *this;
}

bool StatsContainerCmdImpl::isNoStream() const {
    return m_noStream;
}

StatsContainerCmd& StatsContainerCmdImpl::withNoStream(bool noStream) {
    m_noStream = noStream;
    return *this;
}

}
