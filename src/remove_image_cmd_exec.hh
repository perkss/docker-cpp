#ifndef SRC_REMOVE_IMAGE_CMD_EXEC_HPP
#define SRC_REMOVE_IMAGE_CMD_EXEC_HPP

#include <memory>
#include <string>

#include "abstr_sync_docker_cmd_exec.hh"
#include "remove_image_cmd.hh"

namespace dockercpp::command::exec {

class RemoveImageCmdExec
    : public AbstrSyncDockerCmdExec<dockercpp::command::RemoveImageCmd,
                                    std::string>,
      public remove::Exec {
 public:
  RemoveImageCmdExec();
  std::string exec(
      std::shared_ptr<dockercpp::command::RemoveImageCmd> command) override;

  ~RemoveImageCmdExec() {}

 protected:
  std::string execute(
      std::shared_ptr<dockercpp::command::RemoveImageCmd> command) override;
};

}  // namespace dockercpp::command::exec

#endif /* SRC_REMOVE_IMAGE_CMD_EXEC_HPP */
