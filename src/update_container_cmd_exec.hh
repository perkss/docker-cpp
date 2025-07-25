#ifndef SRC_STOP_CONTAINER_CMD_EXEC_HPP
#define SRC_STOP_CONTAINER_CMD_EXEC_HPP

#include "abstr_sync_docker_cmd_exec.hh"
#include "update_container_cmd.hh"

namespace dockercpp::command::exec {
class UpdateContainerCmdExec
    : public AbstrSyncDockerCmdExec<dockercpp::command::UpdateContainerCmd, dockercpp::command::UpdateContainerResponse >,
      public update::Exec {
 public:
  UpdateContainerCmdExec();
  dockercpp::command::UpdateContainerResponse  exec(
      std::shared_ptr<dockercpp::command::UpdateContainerCmd> command) override;

  ~UpdateContainerCmdExec() {}

 protected:
  dockercpp::command::UpdateContainerResponse  execute(
      std::shared_ptr<dockercpp::command::UpdateContainerCmd> command) override;
};
}  // namespace dockercpp::command::exec

#endif /* SRC_STOP_CONTAINER_CMD_EXEC_HPP */
