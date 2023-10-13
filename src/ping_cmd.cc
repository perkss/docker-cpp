#include "ping_cmd.hh"

#include <spdlog/spdlog.h>

namespace dockercpp::command {

PingCmdImpl::PingCmdImpl(std::unique_ptr<ping::Exec> exec)
    : AbstrDockerCmd<PingCmd, std::string>(std::move(exec)) {}

std::string PingCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

}  // namespace dockercpp::command
