#ifndef UNPAUSE_CONTAINER_CMD_HPP
#define UNPAUSE_CONTAINER_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

class UnpauseContainerCmd : public SynchDockerCmd<bool>,
                         public std::enable_shared_from_this<UnpauseContainerCmd> {
 public:
  virtual std::string getContainerId() = 0;
};

namespace unpausecontainer {
class Exec : public exec::DockerCmdSyncExec<UnpauseContainerCmd, bool> {
 public:
  ~Exec() {}
};
}  // namespace unpausecontainer

class UnpauseContainerCmdImpl : public UnpauseContainerCmd,
                             public AbstrDockerCmd<UnpauseContainerCmd, bool> {
 public:
  explicit UnpauseContainerCmdImpl(std::unique_ptr<unpausecontainer::Exec> exec,
                                const std::string& containerId);

  bool exec() override;

  void close() override {}

  std::string getContainerId() override;

  ~UnpauseContainerCmdImpl() {}

 private:
  std::string m_containerId;
};

}  // namespace dockercpp::command
#endif /* UNPAUSE_CONTAINER_CMD_HPP */
