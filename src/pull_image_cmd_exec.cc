#include "pull_image_cmd_exec.hh"

#include "pull_image_cmd.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

PullImageCmdExec::PullImageCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::PullImageCmd, std::string>(),
      pull::Exec() {}

std::string PullImageCmdExec::exec(
    std::shared_ptr<dockercpp::command::PullImageCmd> command) {
  return execute(command);
}

std::string PullImageCmdExec::execute(
    std::shared_ptr<dockercpp::command::PullImageCmd> command) {
  core::WebTarget webResource = m_webTarget->path("/images/create");

  webResource.queryParam("registry", command->getRegistry());
  webResource.queryParam("fromImage", command->getRepository());
  webResource.queryParam("tag", command->getTag());

  std::string emptyBoyd;
  // no body
  std::string response = webResource.request().post(emptyBoyd);
  return "";
}

}  // namespace dockercpp::command::exec
