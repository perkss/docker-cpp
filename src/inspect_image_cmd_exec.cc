#include "inspect_image_cmd_exec.hh"

#include <memory>

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

InspectImageCmdExec::InspectImageCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::InspectImageCmd,
                             model::InspectImageResponse>(),
      inspectimage::Exec() {}

model::InspectImageResponse InspectImageCmdExec::exec(
    std::shared_ptr<dockercpp::command::InspectImageCmd> command) {
  return execute(command);
}

model::InspectImageResponse InspectImageCmdExec::execute(
    std::shared_ptr<dockercpp::command::InspectImageCmd> command) {
  core::WebTarget webResource =
      m_webTarget->path("images/" + command->getImageId() + "/json");

  std::string response = webResource.request().get();

  spdlog::info("converting string {}", response);

  nlohmann::json json = nlohmann::json::parse(response);

  spdlog::info("Parsed json");
  return json.get<model::InspectImageResponse>();
}

}  // namespace dockercpp::command::exec
