#ifndef SRC_INSPECT_CONTAINER_CMD_EXEC_HPP
#define SRC_INSPECT_CONTAINER_CMD_EXEC_HPP

#include "abstr_sync_docker_cmd_exec.hh"
#include "inspect_container_cmd.hh"
#include "inspect_container_response.hh"

namespace dockercpp::command::exec {
class InspectContainerCmdExec
    : public AbstrSyncDockerCmdExec<dockercpp::command::InspectContainerCmd,
                                    model::InspectContainerResponse>,
      public inspectcontainer::Exec {
 public:
  InspectContainerCmdExec();
  model::InspectContainerResponse exec(
      std::shared_ptr<dockercpp::command::InspectContainerCmd> command)
      override;

  ~InspectContainerCmdExec() override = default;

 protected:
  model::InspectContainerResponse execute(
      std::shared_ptr<dockercpp::command::InspectContainerCmd> command)
      override;
};
}  // namespace dockercpp::command::exec

#endif /* SRC_INSPECT_CONTAINER_CMD_EXEC_HPP */
