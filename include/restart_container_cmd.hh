#ifndef RESTART_CONTAINER_CMD_HPP
#define RESTART_CONTAINER_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

class RestartContainerCmd : public SynchDockerCmd<bool>,
                         public std::enable_shared_from_this<RestartContainerCmd> {
 public:
  virtual std::string getContainerId() = 0;
};

namespace restartcontainer {
class Exec : public exec::DockerCmdSyncExec<RestartContainerCmd, bool> {
 public:
  ~Exec() {}
};
}  // namespace restartcontainer

class RestartContainerCmdImpl : public RestartContainerCmd,
                             public AbstrDockerCmd<RestartContainerCmd, bool> {
 public:
  explicit RestartContainerCmdImpl(std::unique_ptr<restartcontainer::Exec> exec,
                                const std::string& containerId);

  bool exec() override;

  void close() override {}

  std::string getContainerId() override;

  ~RestartContainerCmdImpl() {}

 private:
  std::string m_containerId;
};

}  // namespace dockercpp::command
#endif /* RESTART_CONTAINER_CMD_HPP */
