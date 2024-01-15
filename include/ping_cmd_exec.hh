#ifndef SRC_PING_CMD_EXEC_HPP
#define SRC_PING_CMD_EXEC_HPP

#include "abstr_sync_docker_cmd_exec.hh"
#include "ping_cmd.hh"

#include <string>

namespace dockercpp::command::exec {

class PingCmdExec : public AbstrSyncDockerCmdExec<dockercpp::command::PingCmd,
                                                  std::string>,
                    public ping::Exec {
 public:
  PingCmdExec();
  std::string exec(std::shared_ptr<dockercpp::command::PingCmd> command) override;

  ~PingCmdExec() {}

 protected:
  std::string execute(std::shared_ptr<dockercpp::command::PingCmd> command) override;
};

}  // namespace dockercpp::command::exec
#endif /* SRC_PING_CMD_EXEC_HPP */
