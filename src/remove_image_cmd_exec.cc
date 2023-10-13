#include "remove_image_cmd_exec.hh"

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

RemoveImageCmdExec::RemoveImageCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::RemoveImageCmd, std::string>(),
      remove::Exec() {}

std::string RemoveImageCmdExec::exec(
    std::shared_ptr<dockercpp::command::RemoveImageCmd> command) {
  return execute(command);
}

std::string RemoveImageCmdExec::execute(
    std::shared_ptr<dockercpp::command::RemoveImageCmd> command) {
  core::WebTarget webResource =
      m_webTarget->path("/images/" + command->getImageId());

  return webResource.request().deletehttp() ? "true" : "false";
}

}  // namespace dockercpp::command::exec
