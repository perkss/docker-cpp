#ifndef INCLUDE_LOAD_IMAGE_CMD_HPP
#define INCLUDE_LOAD_IMAGE_CMD_HPP

#include <memory>
#include <string>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

class LoadImageCmd : public SynchDockerCmd<std::string>,
                      public std::enable_shared_from_this<LoadImageCmd> {
 public:
  explicit LoadImageCmd(const std::string& tarContents);

  std::string getTarContents();

  ~LoadImageCmd() {}

 private:
  std::string m_tar;
};

namespace load {
class Exec : public exec::DockerCmdSyncExec<LoadImageCmd, std::string> {
 public:
  ~Exec() {}
};
}  // namespace load

class LoadImageCmdImpl : public LoadImageCmd,
                         public AbstrDockerCmd<LoadImageCmd, std::string> {
 public:
  LoadImageCmdImpl(std::unique_ptr<load::Exec> exec, const std::string& tar);

  std::string exec() override;

  void close() override;
  ~LoadImageCmdImpl();

 private:
  std::string m_tar;
};

}  // namespace dockercpp::command

#endif /* INCLUDE_LOAD_IMAGE_CMD_HPP */
