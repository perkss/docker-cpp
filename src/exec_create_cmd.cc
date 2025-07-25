#include "exec_create_cmd.hh"

namespace dockercpp::command {

ExecCreateCmdImpl::ExecCreateCmdImpl(std::unique_ptr<exec::CreateExec> exec)
    : AbstrDockerCmd<ExecCreateCmd, ExecCreateResponse>(std::move(exec)),
      m_attachStdin(false),
      m_attachStdout(true),
      m_attachStderr(true),
      m_tty(false),
      m_privileged(false) {}

ExecCreateResponse ExecCreateCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

std::string ExecCreateCmdImpl::getContainerId() const {
    return m_containerId;
}

ExecCreateCmd& ExecCreateCmdImpl::withContainerId(const std::string& id) {
    m_containerId = id;
    return *this;
}

std::vector<std::string> ExecCreateCmdImpl::getCmd() const {
    return m_cmd;
}

ExecCreateCmd& ExecCreateCmdImpl::withCmd(const std::vector<std::string>& cmd) {
    m_cmd = cmd;
    return *this;
}

bool ExecCreateCmdImpl::isAttachStdin() const {
    return m_attachStdin;
}

ExecCreateCmd& ExecCreateCmdImpl::withAttachStdin(bool attachStdin) {
    m_attachStdin = attachStdin;
    return *this;
}

bool ExecCreateCmdImpl::isAttachStdout() const {
    return m_attachStdout;
}

ExecCreateCmd& ExecCreateCmdImpl::withAttachStdout(bool attachStdout) {
    m_attachStdout = attachStdout;
    return *this;
}

bool ExecCreateCmdImpl::isAttachStderr() const {
    return m_attachStderr;
}

ExecCreateCmd& ExecCreateCmdImpl::withAttachStderr(bool attachStderr) {
    m_attachStderr = attachStderr;
    return *this;
}

bool ExecCreateCmdImpl::isTty() const {
    return m_tty;
}

ExecCreateCmd& ExecCreateCmdImpl::withTty(bool tty) {
    m_tty = tty;
    return *this;
}

std::string ExecCreateCmdImpl::getUser() const {
    return m_user;
}

ExecCreateCmd& ExecCreateCmdImpl::withUser(const std::string& user) {
    m_user = user;
    return *this;
}

bool ExecCreateCmdImpl::isPrivileged() const {
    return m_privileged;
}

ExecCreateCmd& ExecCreateCmdImpl::withPrivileged(bool privileged) {
    m_privileged = privileged;
    return *this;
}

}
