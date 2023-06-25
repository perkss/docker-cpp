#include "version_cmd.hh"

namespace dockercpp::command {

VersionCmdImpl::VersionCmdImpl(std::unique_ptr<version::Exec> exec)
    : AbstrDockerCmd<VersionCmd, model::Version>(std::move(exec)) {}

model::Version VersionCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

}  // namespace dockercpp::command
