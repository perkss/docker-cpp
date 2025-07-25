#include "exec_start_cmd.hh"

namespace dockercpp::command {

ExecStartCmdImpl::ExecStartCmdImpl(std::unique_ptr<exec::StartExec> exec)
    : AbstrDockerCmd<ExecStartCmd, void>(std::move(exec)),
      m_detach(false),
      m_tty(false) {}

void ExecStartCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

std::string ExecStartCmdImpl::getExecId() const {
    return m_execId;
}

ExecStartCmd& ExecStartCmdImpl::withExecId(const std::string& execId) {
    m_execId = execId;
    return *this;
}

bool ExecStartCmdImpl::isDetach() const {
    return m_detach;
}

ExecStartCmd& ExecStartCmdImpl::withDetach(bool detach) {
    m_detach = detach;
    return *this;
}

bool ExecStartCmdImpl::isTty() const {
    return m_tty;
}

ExecStartCmd& ExecStartCmdImpl::withTty(bool tty) {
    m_tty = tty;
    return *this;
}

}
