#ifndef PAUSE_CONTAINER_CMD_HPP
#define PAUSE_CONTAINER_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

class PauseContainerCmd : public SynchDockerCmd<bool>,
                         public std::enable_shared_from_this<PauseContainerCmd> {
 public:
  virtual std::string getContainerId() = 0;
};

namespace pausecontainer {
class Exec : public exec::DockerCmdSyncExec<PauseContainerCmd, bool> {
 public:
  ~Exec() {}
};
}  // namespace pausecontainer

class PauseContainerCmdImpl : public PauseContainerCmd,
                             public AbstrDockerCmd<PauseContainerCmd, bool> {
 public:
  explicit PauseContainerCmdImpl(std::unique_ptr<pausecontainer::Exec> exec,
                                const std::string& containerId);

  bool exec() override;

  void close() override {}

  std::string getContainerId() override;

  ~PauseContainerCmdImpl() {}

 private:
  std::string m_containerId;
};

}  // namespace dockercpp::command
#endif /* PAUSE_CONTAINER_CMD_HPP */
