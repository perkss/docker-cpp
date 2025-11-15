#ifndef KILL_CONTAINER_CMD_HPP
#define KILL_CONTAINER_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

class KillContainerCmd : public SynchDockerCmd<bool>,
                         public std::enable_shared_from_this<KillContainerCmd> {
 public:
  virtual std::string getContainerId() = 0;
};

namespace killcontainer {
class Exec : public exec::DockerCmdSyncExec<KillContainerCmd, bool> {
 public:
  ~Exec() {}
};
}  // namespace killcontainer

class KillContainerCmdImpl : public KillContainerCmd,
                             public AbstrDockerCmd<KillContainerCmd, bool> {
 public:
  explicit KillContainerCmdImpl(std::unique_ptr<killcontainer::Exec> exec,
                                const std::string& containerId);

  bool exec() override;

  void close() override {}

  std::string getContainerId() override;

  ~KillContainerCmdImpl() {}

 private:
  std::string m_containerId;
};

}  // namespace dockercpp::command
#endif /* KILL_CONTAINER_CMD_HPP */
