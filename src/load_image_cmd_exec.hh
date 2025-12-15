#ifndef LOAD_IMAGE_CMD_EXEC_HH
#define LOAD_IMAGE_CMD_EXEC_HH

#include "abstr_sync_docker_cmd_exec.hh"
#include "load_image_cmd.hh"

namespace dockercpp::command::exec {

class LoadImageCmdExec
    : public AbstrSyncDockerCmdExec<dockercpp::command::LoadImageCmd, std::string>,
      public load::Exec {
 public:
  LoadImageCmdExec();

  std::string exec(std::shared_ptr<dockercpp::command::LoadImageCmd> command) override;

  std::string execute(std::shared_ptr<dockercpp::command::LoadImageCmd> command) override;
  ~LoadImageCmdExec() {}
};

}  // namespace dockercpp::command::exec

#endif
