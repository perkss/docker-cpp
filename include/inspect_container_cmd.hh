#ifndef INCLUDE_INSPECT_CONTAINER_CMD_HPP
#define INCLUDE_INSPECT_CONTAINER_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "inspect_container_response.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {
class InspectContainerCmd
    : public SynchDockerCmd<model::InspectContainerResponse>,
      public std::enable_shared_from_this<InspectContainerCmd> {
 public:
  virtual std::string getContainerId() = 0;
};

namespace inspectcontainer {
class Exec : public exec::DockerCmdSyncExec<InspectContainerCmd,
                                            model::InspectContainerResponse> {
 public:
  ~Exec() override = default;
};
}  // namespace inspectcontainer

class InspectContainerCmdImpl
    : public InspectContainerCmd,
      public AbstrDockerCmd<InspectContainerCmd,
                            model::InspectContainerResponse> {
 public:
  InspectContainerCmdImpl(std::unique_ptr<inspectcontainer::Exec> exec,
                          const std::string& containerId);

  model::InspectContainerResponse exec() override;

  void close() override {}

  std::string getContainerId() override;

  ~InspectContainerCmdImpl() override = default;

 private:
  std::string m_containerId;
};
}  // namespace dockercpp::command
#endif /* INCLUDE_INSPECT_CONTAINER_CMD_HPP */
