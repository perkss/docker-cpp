#include "inspect_container_cmd_exec.hh"

#include <memory>

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

InspectContainerCmdExec::InspectContainerCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::InspectContainerCmd,
                             model::InspectContainerResponse>(),
      inspectcontainer::Exec() {}

model::InspectContainerResponse InspectContainerCmdExec::exec(
    std::shared_ptr<dockercpp::command::InspectContainerCmd> command) {
  return execute(command);
}

model::InspectContainerResponse InspectContainerCmdExec::execute(
    std::shared_ptr<dockercpp::command::InspectContainerCmd> command) {
  core::WebTarget webResource =
      m_webTarget->path("containers/" + command->getContainerId() + "/json");

  std::string response = webResource.request().get();

  spdlog::info("converting string {}", response);

  nlohmann::json json = nlohmann::json::parse(response);

  spdlog::info("Parsed json");
  return json.get<model::InspectContainerResponse>();
}

}  // namespace dockercpp::command::exec
