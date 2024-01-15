#include "create_container_cmd_exec.hh"

#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

CreateContainerCmdExec::CreateContainerCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::CreateContainerCmd,
                             model::CreateContainerResponse>(),
      createcontainer::Exec() {}

model::CreateContainerResponse CreateContainerCmdExec::exec(
    std::shared_ptr<dockercpp::command::CreateContainerCmd> command) {
  spdlog::info("Exec called in the CreateContainercmd exec");
  return execute(command);
}

model::CreateContainerResponse CreateContainerCmdExec::execute(
    std::shared_ptr<dockercpp::command::CreateContainerCmd> command) {
  spdlog::info("Execute called in the CreateContainer cmd exec");
  core::WebTarget webResource = m_webTarget->path("/containers/create");

  const nlohmann::json request = command->getRequest();

  std::string body = request.dump();

  std::string response = webResource.request().post(body);

  spdlog::info("converting string {}", response);

  nlohmann::json json = nlohmann::json::parse(response);

  spdlog::info("Parsed json {}", json.dump());
  return json.get<model::CreateContainerResponse>();
}

}  // namespace dockercpp::command::exec
