#ifndef SRC_INSPECT_IMAGE_CMD_EXEC_HPP
#define SRC_INSPECT_IMAGE_CMD_EXEC_HPP

#include "abstr_sync_docker_cmd_exec.hh"
#include "inspect_image_cmd.hh"
#include "inspect_image_response.hh"

namespace dockercpp::command::exec {
class InspectImageCmdExec
    : public AbstrSyncDockerCmdExec<dockercpp::command::InspectImageCmd,
                                    model::InspectImageResponse>,
      public inspectimage::Exec {
 public:
  InspectImageCmdExec();
  model::InspectImageResponse exec(
      std::shared_ptr<dockercpp::command::InspectImageCmd> command) override;

  ~InspectImageCmdExec() {}

 protected:
  model::InspectImageResponse execute(
      std::shared_ptr<dockercpp::command::InspectImageCmd> command) override;
};
}  // namespace dockercpp::command::exec

#endif /* SRC_INSPECT_IMAGE_CMD_EXEC_HPP */
