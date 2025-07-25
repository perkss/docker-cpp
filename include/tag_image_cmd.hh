#ifndef TAG_IMAGE_CMD_HPP
#define TAG_IMAGE_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

class TagImageCmd : public SynchDockerCmd<bool>,
                   public std::enable_shared_from_this<TagImageCmd> {
 public:
  virtual std::string getImageId() = 0;
  virtual std::string getRepository() = 0;
  virtual std::string getTag() = 0;
};

namespace tagimage {
class Exec : public exec::DockerCmdSyncExec<TagImageCmd, bool> {
 public:
  ~Exec() {}
};
}  // namespace tagimage

class TagImageCmdImpl : public TagImageCmd,
                       public AbstrDockerCmd<TagImageCmd, bool> {
 public:
  explicit TagImageCmdImpl(std::unique_ptr<tagimage::Exec> exec,
                          const std::string& imageId,
                          const std::string& repository,
                          const std::string& tag);

  bool exec() override;

  void close() override {}

  std::string getImageId() override;
  std::string getRepository() override;
  std::string getTag() override;

  ~TagImageCmdImpl() {}

 private:
  std::string m_imageId;
  std::string m_repository;
  std::string m_tag;
};

}  // namespace dockercpp::command
#endif /* TAG_IMAGE_CMD_HPP */
