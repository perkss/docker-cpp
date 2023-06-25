#ifndef SRC_CREATE_CONTAINER_CMD_EXEC_HPP
#define SRC_CREATE_CONTAINER_CMD_EXEC_HPP

#include "abstr_sync_docker_cmd_exec.hh"
#include "create_container_cmd.hh"
#include "create_container_response.hh"

namespace dockercpp::command::exec {
class CreateContainerCmdExec

    : public AbstrSyncDockerCmdExec<dockercpp::command::CreateContainerCmd,
                                    model::CreateContainerResponse>,
      public createcontainer::Exec {
 public:
  CreateContainerCmdExec();
  model::CreateContainerResponse exec(
      std::shared_ptr<dockercpp::command::CreateContainerCmd> command) override;

  ~CreateContainerCmdExec() {}

 protected:
  model::CreateContainerResponse execute(
      std::shared_ptr<dockercpp::command::CreateContainerCmd> command) override;
};
}  // namespace dockercpp::command::exec

#endif /* SRC_CREATE_CONTAINER_CMD_EXEC_HPP */
