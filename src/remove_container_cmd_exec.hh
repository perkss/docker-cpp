#ifndef SRC_REMOVE_CONTAINER_CMD_EXEC_HPP
#define SRC_REMOVE_CONTAINER_CMD_EXEC_HPP

#include <string>

#include "abstr_sync_docker_cmd_exec.hh"
#include "remove_container_cmd.hh"

namespace dockercpp::command::exec {

class RemoveContainerCmdExec
    : public AbstrSyncDockerCmdExec<dockercpp::command::RemoveContainerCmd,
                                    std::string>,
      public removecontainer::Exec {
 public:
  RemoveContainerCmdExec();
  std::string exec(
      std::shared_ptr<dockercpp::command::RemoveContainerCmd> command) override;

  ~RemoveContainerCmdExec() {}

 protected:
  std::string execute(
      std::shared_ptr<dockercpp::command::RemoveContainerCmd> command) override;
};

}  // namespace dockercpp::command::exec

#endif /* SRC_REMOVE_CONTAINER_CMD_EXEC_HPP */
