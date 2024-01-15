#include "stop_container_cmd_exec.hh"

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

StopContainerCmdExec::StopContainerCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::StopContainerCmd, bool>(),
      stopcontainer::Exec() {}

bool StopContainerCmdExec::exec(
    std::shared_ptr<dockercpp::command::StopContainerCmd> command) {
  return execute(command);
}

bool StopContainerCmdExec::execute(
    std::shared_ptr<dockercpp::command::StopContainerCmd> command) {
  core::WebTarget webResource =
      m_webTarget->path("/containers/" + command->getContainerId() + "/stop");

  std::string emptyBoyd = "";
  // no body
  std::string response = webResource.request().post(emptyBoyd);

  return true;
}

}  // namespace dockercpp::command::exec
