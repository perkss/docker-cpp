#ifndef ATTACH_CONTAINER_CMD_HPP
#define ATTACH_CONTAINER_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

class AttachContainerCmd : public SynchDockerCmd<bool>,
                         public std::enable_shared_from_this<AttachContainerCmd> {
 public:
  virtual std::string getContainerId() = 0;
};

namespace attachcontainer {
class Exec : public exec::DockerCmdSyncExec<AttachContainerCmd, bool> {
 public:
  ~Exec() {}
};
}  // namespace attachcontainer

class AttachContainerCmdImpl : public AttachContainerCmd,
                             public AbstrDockerCmd<AttachContainerCmd, bool> {
 public:
  explicit AttachContainerCmdImpl(std::unique_ptr<attachcontainer::Exec> exec,
                                const std::string& containerId);

  bool exec() override;

  void close() override {}

  std::string getContainerId() override;

  ~AttachContainerCmdImpl() {}

 private:
  std::string m_containerId;
};

}  // namespace dockercpp::command
#endif /* ATTACH_CONTAINER_CMD_HPP */
