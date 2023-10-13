#include "remove_container_cmd_exec.hh"

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {
RemoveContainerCmdExec::RemoveContainerCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::RemoveContainerCmd,
                             std::string>(),
      removecontainer::Exec() {}

std::string RemoveContainerCmdExec::exec(
    std::shared_ptr<dockercpp::command::RemoveContainerCmd> command) {
  return execute(command);
}

std::string RemoveContainerCmdExec::execute(
    std::shared_ptr<dockercpp::command::RemoveContainerCmd> command) {
  core::WebTarget webResource =
      m_webTarget->path("/containers/" + command->getContainerId());

  return webResource.request().deletehttp() ? "true" : "false";
}

}  // namespace dockercpp::command::exec
