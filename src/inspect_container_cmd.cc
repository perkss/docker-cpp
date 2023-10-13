#include "inspect_container_cmd.hh"

namespace dockercpp::command {

InspectContainerCmdImpl::InspectContainerCmdImpl(
    std::unique_ptr<inspectcontainer::Exec> exec,
    const std::string& containerId)
    : AbstrDockerCmd<InspectContainerCmd, model::InspectContainerResponse>(
          std::move(exec)),
      m_containerId(containerId) {}

model::InspectContainerResponse InspectContainerCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

std::string InspectContainerCmdImpl::getContainerId() { return m_containerId; }

}  // namespace dockercpp::command
