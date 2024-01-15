#include "info_cmd_exec.hh"

#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

InfoCmdExec::InfoCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::InfoCmd,
                             dockercpp::model::Info>(),
      info::Exec() {}

dockercpp::model::Info InfoCmdExec::exec(
    std::shared_ptr<dockercpp::command::InfoCmd> command) {
  return execute(command);
}

dockercpp::model::Info InfoCmdExec::execute(
    std::shared_ptr<dockercpp::command::InfoCmd> command) {
  core::WebTarget webResource = m_webTarget->path("info");

  auto response = webResource.request().get();

  spdlog::info("converting string {}", response);

  const nlohmann::json json = nlohmann::json::parse(response);

  spdlog::info("Parsed json");
  auto result = json.get<model::Info>();
  spdlog::info("Parsed json result");
  return result;
}

}  // namespace dockercpp::command::exec
