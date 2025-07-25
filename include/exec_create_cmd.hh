#ifndef EXEC_CREATE_CMD_HPP
#define EXEC_CREATE_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

struct ExecCreateResponse {
    std::string id;
    nlohmann::json warnings;
};

class ExecCreateCmd : public SynchDockerCmd<ExecCreateResponse>,
                     public std::enable_shared_from_this<ExecCreateCmd> {
 public:
  virtual std::string getContainerId() const = 0;
  virtual ExecCreateCmd& withContainerId(const std::string& id) = 0;
  virtual std::vector<std::string> getCmd() const = 0;
  virtual ExecCreateCmd& withCmd(const std::vector<std::string>& cmd) = 0;
  virtual bool isAttachStdin() const = 0;
  virtual ExecCreateCmd& withAttachStdin(bool attachStdin) = 0;
  virtual bool isAttachStdout() const = 0;
  virtual ExecCreateCmd& withAttachStdout(bool attachStdout) = 0;
  virtual bool isAttachStderr() const = 0;
  virtual ExecCreateCmd& withAttachStderr(bool attachStderr) = 0;
  virtual bool isTty() const = 0;
  virtual ExecCreateCmd& withTty(bool tty) = 0;
  virtual std::string getUser() const = 0;
  virtual ExecCreateCmd& withUser(const std::string& user) = 0;
  virtual bool isPrivileged() const = 0;
  virtual ExecCreateCmd& withPrivileged(bool privileged) = 0;
};

namespace exec {
class CreateExec : public exec::DockerCmdSyncExec<ExecCreateCmd, ExecCreateResponse> {
 public:
  ~CreateExec() {}
};
}  // namespace exec

class ExecCreateCmdImpl : public ExecCreateCmd,
                         public AbstrDockerCmd<ExecCreateCmd, ExecCreateResponse> {
 public:
  explicit ExecCreateCmdImpl(std::unique_ptr<exec::CreateExec> exec);

  ExecCreateResponse exec() override;

  void close() override {}

  std::string getContainerId() const override;
  ExecCreateCmd& withContainerId(const std::string& id) override;
  std::vector<std::string> getCmd() const override;
  ExecCreateCmd& withCmd(const std::vector<std::string>& cmd) override;
  bool isAttachStdin() const override;
  ExecCreateCmd& withAttachStdin(bool attachStdin) override;
  bool isAttachStdout() const override;
  ExecCreateCmd& withAttachStdout(bool attachStdout) override;
  bool isAttachStderr() const override;
  ExecCreateCmd& withAttachStderr(bool attachStderr) override;
  bool isTty() const override;
  ExecCreateCmd& withTty(bool tty) override;
  std::string getUser() const override;
  ExecCreateCmd& withUser(const std::string& user) override;
  bool isPrivileged() const override;
  ExecCreateCmd& withPrivileged(bool privileged) override;

  ~ExecCreateCmdImpl() {}

 private:
  std::string m_containerId;
  std::vector<std::string> m_cmd;
  bool m_attachStdin;
  bool m_attachStdout;
  bool m_attachStderr;
  bool m_tty;
  std::string m_user;
  bool m_privileged;
};

}  // namespace dockercpp::command
#endif /* EXEC_CREATE_CMD_HPP */
