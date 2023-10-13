#ifndef SRC_STOP_CONTAINER_CMD_EXEC_HPP
#define SRC_STOP_CONTAINER_CMD_EXEC_HPP

#include "abstr_sync_docker_cmd_exec.hh"
#include "stop_container_cmd.hh"

namespace dockercpp::command::exec {
class StopContainerCmdExec
    : public AbstrSyncDockerCmdExec<dockercpp::command::StopContainerCmd, bool>,
      public stopcontainer::Exec {
 public:
  StopContainerCmdExec();
  bool exec(
      std::shared_ptr<dockercpp::command::StopContainerCmd> command) override;

  ~StopContainerCmdExec() {}

 protected:
  bool execute(
      std::shared_ptr<dockercpp::command::StopContainerCmd> command) override;
};
}  // namespace dockercpp::command::exec

#endif /* SRC_STOP_CONTAINER_CMD_EXEC_HPP */
