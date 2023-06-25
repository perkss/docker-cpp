#ifndef INCLUDE_START_CONTAINER_CMD_HPP
#define INCLUDE_START_CONTAINER_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {
class StartContainerCmd
    : public SynchDockerCmd<bool>,
      public std::enable_shared_from_this<StartContainerCmd> {

  public:
  virtual std::string getContainerId() = 0;
};

namespace startcontainer {
class Exec : public exec::DockerCmdSyncExec<StartContainerCmd, bool> {
 public:
  ~Exec() {}
};
}  // namespace startcontainer

class StartContainerCmdImpl : public StartContainerCmd,
                              public AbstrDockerCmd<StartContainerCmd, bool> {
 public:
  explicit StartContainerCmdImpl(std::unique_ptr<startcontainer::Exec> exec,
                                 std::string containerId);

  bool exec() override;

  void close() override {}

  std::string getContainerId() override;

  ~StartContainerCmdImpl() {}

 private:
  std::string m_containerId;
};

}  // namespace dockercpp::command

#endif /* INCLUDE_START_CONTAINER_CMD_HPP */
