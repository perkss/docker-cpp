#include "info_cmd.hh"

namespace dockercpp::command {

InfoCmdImpl::InfoCmdImpl(std::unique_ptr<info::Exec> exec)
    : AbstrDockerCmd<InfoCmd, dockercpp::model::Info>(std::move(exec)) {}

dockercpp::model::Info InfoCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

}  // namespace dockercpp::command
