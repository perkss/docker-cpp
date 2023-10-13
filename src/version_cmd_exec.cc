#include "version_cmd_exec.hh"

#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

VersionCmdExec::VersionCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::VersionCmd, model::Version>(),
      version::Exec() {}

model::Version VersionCmdExec::exec(
    std::shared_ptr<dockercpp::command::VersionCmd> command) {
  spdlog::info("Exec called in the Versioncmd exec");
  return execute(command);
}

model::Version VersionCmdExec::execute(
    std::shared_ptr<dockercpp::command::VersionCmd> command) {
  spdlog::info("Execute called in the Version cmd exec");
  core::WebTarget webResource = m_webTarget->path("version");

  std::string response = webResource.request().get();

  spdlog::info("converting string {}", response);

  nlohmann::json json = nlohmann::json::parse(response);

  spdlog::info("Parsed json");
  return json.get<model::Version>();
}

}  // namespace dockercpp::command::exec
