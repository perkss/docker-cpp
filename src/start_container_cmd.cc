#include "start_container_cmd.hh"

namespace dockercpp::command {

StartContainerCmdImpl::StartContainerCmdImpl(
    std::unique_ptr<startcontainer::Exec> exec, std::string containerId)
    : AbstrDockerCmd<StartContainerCmd, bool>(std::move(exec)),
      m_containerId(containerId) {}

bool StartContainerCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

std::string StartContainerCmdImpl::getContainerId() { return m_containerId; }

}  // namespace dockercpp::command
