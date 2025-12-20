#include "load_image_cmd_exec.hh"

#include <spdlog/spdlog.h>

#include "abstr_sync_docker_cmd_exec.hh"
#include "docker_exception.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

LoadImageCmdExec::LoadImageCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::LoadImageCmd, std::string>(),
      load::Exec() {}

std::string LoadImageCmdExec::exec(
    std::shared_ptr<dockercpp::command::LoadImageCmd> command) {
  return execute(command);
}

std::string LoadImageCmdExec::execute(
    std::shared_ptr<dockercpp::command::LoadImageCmd> command) {
  core::WebTarget webResource = m_webTarget->path("/images/load");

  auto body = command->getTarContents();

  auto [response, statusCode] = webResource.request().post_with_code(body);

  if (statusCode != 200) {
    throw dockercpp::DockerException("Error loading image", statusCode, response);
  }

  return response;
}

}  // namespace dockercpp::command::exec
