#include "ping_cmd_exec.hh"

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

PingCmdExec::PingCmdExec()
    : AbstrSyncDockerCmdExec<dockercpp::command::PingCmd, std::string>(),
      ping::Exec() {}

std::string PingCmdExec::exec(
    std::shared_ptr<dockercpp::command::PingCmd> command) {
  spdlog::info("Exec called in the Pingcmd exec");
  return execute(command);
}

std::string PingCmdExec::execute(
    std::shared_ptr<dockercpp::command::PingCmd> command) {
  spdlog::info("Execute called in the Pingcmd exec");
  core::WebTarget webResource = m_webTarget->path("_ping");

  return webResource.request().get();
}

}  // namespace dockercpp::command::exec
