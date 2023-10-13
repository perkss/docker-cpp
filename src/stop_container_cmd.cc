#include "stop_container_cmd.hh"

namespace dockercpp::command {

StopContainerCmdImpl::StopContainerCmdImpl(
    std::unique_ptr<stopcontainer::Exec> exec, const std::string& containerId)
    : AbstrDockerCmd<StopContainerCmd, bool>(std::move(exec)),
      m_containerId(containerId) {}

bool StopContainerCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

std::string StopContainerCmdImpl::getContainerId() { return m_containerId; }

}  // namespace dockercpp::command
