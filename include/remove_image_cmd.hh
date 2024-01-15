#ifndef INCLUDE_REMOVE_IMAGE_CMD_HPP
#define INCLUDE_REMOVE_IMAGE_CMD_HPP

#include <memory>
#include <string>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

class RemoveImageCmd : public SynchDockerCmd<std::string>,
                       public std::enable_shared_from_this<RemoveImageCmd> {
 public:
  virtual std::string getImageId() = 0;

  virtual bool hasForcedEnabled() = 0;

  virtual bool hasNoPruneEnabled() = 0;

  virtual void withForce(bool force) = 0;

  virtual void withNoPrune(bool force) = 0;

  ~RemoveImageCmd() {}
};

namespace remove {
class Exec : public exec::DockerCmdSyncExec<RemoveImageCmd, std::string> {
 public:
  ~Exec() {}
};

}  // namespace remove

class RemoveImageCmdImpl : public RemoveImageCmd,
                           public AbstrDockerCmd<RemoveImageCmd, std::string> {
 public:
  RemoveImageCmdImpl(std::unique_ptr<remove::Exec> exec, const std::string& id);

  std::string getImageId() override;

  bool hasForcedEnabled() override;

  bool hasNoPruneEnabled() override;

  void withForce(bool force) override;

  void withNoPrune(bool force) override;

  std::string exec() override;

  void close() override {}
  ~RemoveImageCmdImpl() {}

 private:
  std::string m_id;
};

}  // namespace dockercpp::command

#endif /* INCLUDE_REMOVE_IMAGE_CMD_HPP */
