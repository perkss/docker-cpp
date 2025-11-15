#include "update_container_cmd_exec.hh"

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

#include <memory>

namespace dockercpp::command::exec {

UpdateContainerCmdExec::UpdateContainerCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::UpdateContainerCmd, dockercpp::command::UpdateContainerResponse >(),
      update::Exec() {}

dockercpp::command::UpdateContainerResponse  UpdateContainerCmdExec::exec(
    std::shared_ptr<dockercpp::command::UpdateContainerCmd> command) {
  return execute(command);
}

dockercpp::command::UpdateContainerResponse  UpdateContainerCmdExec::execute(
    std::shared_ptr<dockercpp::command::UpdateContainerCmd> command) {
  core::WebTarget webResource =
      m_webTarget->path("/containers/" + command->getContainerId() + "/update");

  std::string emptyBoyd = "";
  // no body
  std::string response = webResource.request().post(emptyBoyd);

  return dockercpp::command::UpdateContainerResponse{};
}

}  // namespace dockercpp::command::exec
