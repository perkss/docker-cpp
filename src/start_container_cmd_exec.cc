#include "start_container_cmd_exec.hh"

#include <memory>

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

StartContainerCmdExec::StartContainerCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::StartContainerCmd, bool>(),
      startcontainer::Exec() {}

bool StartContainerCmdExec::exec(
    std::shared_ptr<dockercpp::command::StartContainerCmd> command) {
  return execute(command);
}

bool StartContainerCmdExec::execute(
    std::shared_ptr<dockercpp::command::StartContainerCmd> command) {
  core::WebTarget webResource =
      m_webTarget->path("/containers/" + command->getContainerId() + "/start");

  std::string emptyBoyd = "";
  // no body
  std::string response = webResource.request().post(emptyBoyd);

  return true;
}

}  // namespace dockercpp::command::exec
