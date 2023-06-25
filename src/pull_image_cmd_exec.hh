#ifndef SRC_PULL_IMAGE_CMD_EXEC_HPP
#define SRC_PULL_IMAGE_CMD_EXEC_HPP

#include <string>

#include "abstr_sync_docker_cmd_exec.hh"
#include "pull_image_cmd.hh"

namespace dockercpp::command::exec {

class PullImageCmdExec
    : public AbstrSyncDockerCmdExec<dockercpp::command::PullImageCmd,
                                    std::string>,
      public pull::Exec {
 public:
  PullImageCmdExec();

  std::string exec(
      std::shared_ptr<dockercpp::command::PullImageCmd> command) override;

  ~PullImageCmdExec() {}

 protected:
  std::string execute(
      std::shared_ptr<dockercpp::command::PullImageCmd> command) override;
};

}  // namespace dockercpp::command::exec
#endif /* SRC_PULL_IMAGE_CMD_EXEC_HPP */
