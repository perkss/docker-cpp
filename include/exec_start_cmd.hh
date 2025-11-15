#ifndef EXEC_START_CMD_HPP
#define EXEC_START_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

class ExecStartCmd : public SynchDockerCmd<void>,
                    public std::enable_shared_from_this<ExecStartCmd> {
 public:
  virtual std::string getExecId() const = 0;
  virtual ExecStartCmd& withExecId(const std::string& execId) = 0;
  virtual bool isDetach() const = 0;
  virtual ExecStartCmd& withDetach(bool detach) = 0;
  virtual bool isTty() const = 0;
  virtual ExecStartCmd& withTty(bool tty) = 0;
};

namespace exec {
class StartExec : public exec::DockerCmdSyncExec<ExecStartCmd, void> {
 public:
  ~StartExec() {}
};
}  // namespace exec

class ExecStartCmdImpl : public ExecStartCmd,
                        public AbstrDockerCmd<ExecStartCmd, void> {
 public:
  explicit ExecStartCmdImpl(std::unique_ptr<exec::StartExec> exec);

  void exec() override;

  void close() override {}

  std::string getExecId() const override;
  ExecStartCmd& withExecId(const std::string& execId) override;
  bool isDetach() const override;
  ExecStartCmd& withDetach(bool detach) override;
  bool isTty() const override;
  ExecStartCmd& withTty(bool tty) override;

  ~ExecStartCmdImpl() {}

 private:
  std::string m_execId;
  bool m_detach;
  bool m_tty;
};

}  // namespace dockercpp::command
#endif /* EXEC_START_CMD_HPP */
