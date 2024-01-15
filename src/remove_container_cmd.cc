#include "remove_container_cmd.hh"

namespace dockercpp::command {

RemoveContainerCmdImpl::RemoveContainerCmdImpl(
    std::unique_ptr<removecontainer::Exec> exec, std::string containerId)
    : AbstrDockerCmd<RemoveContainerCmd, std::string>(std::move(exec)) {
  RemoveContainerCmdImpl::withContainerId(containerId);
}

std::string RemoveContainerCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

void RemoveContainerCmdImpl::withContainerId(std::string id) { m_id = id; }

std::string RemoveContainerCmdImpl::getContainerId() { return m_id; }

}  // namespace dockercpp::command
