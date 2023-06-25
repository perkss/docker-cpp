#ifndef SRC_START_CONTAINER_CMD_EXEC_HPP
#define SRC_START_CONTAINER_CMD_EXEC_HPP

#include "abstr_sync_docker_cmd_exec.hh"
#include "start_container_cmd.hh"

namespace dockercpp::command::exec {
class StartContainerCmdExec
    : public AbstrSyncDockerCmdExec<dockercpp::command::StartContainerCmd,
                                    bool>,
      public startcontainer::Exec {
 public:
  StartContainerCmdExec();
  bool exec(
      std::shared_ptr<dockercpp::command::StartContainerCmd> command) override;

  ~StartContainerCmdExec() {}

 protected:
  bool execute(
      std::shared_ptr<dockercpp::command::StartContainerCmd> command) override;
};
}  // namespace dockercpp::command::exec

#endif /* SRC_START_CONTAINER_CMD_EXEC_HPP */
