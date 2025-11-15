#ifndef STOP_CONTAINER_CMD_HPP
#define STOP_CONTAINER_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {
class StopContainerCmd : public SynchDockerCmd<bool>,
                         public std::enable_shared_from_this<StopContainerCmd> {
 public:
  virtual std::string getContainerId() = 0;
};

namespace stopcontainer {
class Exec : public exec::DockerCmdSyncExec<StopContainerCmd, bool> {
 public:
  ~Exec() {}
};
}  // namespace stopcontainer

class StopContainerCmdImpl : public StopContainerCmd,
                             public AbstrDockerCmd<StopContainerCmd, bool> {
 public:
  explicit StopContainerCmdImpl(std::unique_ptr<stopcontainer::Exec> exec,
                                const std::string& containerId);

  bool exec() override;

  void close() override {}

  std::string getContainerId() override;

  ~StopContainerCmdImpl() = default;

 private:
  std::string m_containerId;
};

}
#endif /* STOP_CONTAINER_CMD_HPP */
