#ifndef PULL_IMAGE_MD_H
#define PULL_IMAGE_MD_H

#include <memory>
#include <string>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

class PullImageCmd : public SynchDockerCmd<std::string>,
                     public std::enable_shared_from_this<PullImageCmd> {
 public:
  explicit PullImageCmd(const std::string& image);

  PullImageCmd& withTag(std::string tag);

  std::string getRepository();

  std::string getTag();

  std::string getRegistry();

  std::string getPlatform();

  ~PullImageCmd() {}

 private:
  std::string m_repository;
  std::string m_tag;
  std::string m_registry;
  std::string m_platform;
};

namespace pull {
class Exec : public exec::DockerCmdSyncExec<PullImageCmd, std::string> {
 public:
  ~Exec() {}
};
}  // namespace pull

class PullImageCmdImpl : public PullImageCmd,
                         public AbstrDockerCmd<PullImageCmd, std::string> {
 public:
  PullImageCmdImpl(std::unique_ptr<pull::Exec> exec, const std::string& image);

  std::string exec() override;

  void close() override;
  ~PullImageCmdImpl();
};

};  // namespace dockercpp::command
#endif
