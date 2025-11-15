#include "remove_image_cmd_exec.hh"

#include <spdlog/spdlog.h>

#include "abstr_sync_docker_cmd_exec.hh"
#include "docker_exception.hh"
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

  auto [response, statusCode] = webResource.request().deletehttp_with_code();
  
  if (statusCode == 404) {
    throw dockercpp::NotFoundException("No such image: " + command->getImageId());
  } else if (statusCode != 200) {
    throw dockercpp::DockerException("Error removing image", statusCode, response);
  }

  return response;
}

}  // namespace dockercpp::command::exec
