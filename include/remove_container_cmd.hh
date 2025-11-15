#ifndef INCLUDE_REMOVE_CONTAINER_CMD_HPP
#define INCLUDE_REMOVE_CONTAINER_CMD_HPP

#include <memory>
#include <string>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

class RemoveContainerCmd
    : public SynchDockerCmd<std::string>,
      public std::enable_shared_from_this<RemoveContainerCmd> {
 public:
  virtual void withContainerId(std::string id) = 0;
  virtual std::string getContainerId() = 0;
  virtual bool hasForceEnabled() const = 0;
  virtual RemoveContainerCmd& withForce(bool force) = 0;

  ~RemoveContainerCmd() {}

 protected:
  std::string m_id;
};

namespace removecontainer {
class Exec : public exec::DockerCmdSyncExec<RemoveContainerCmd, std::string> {
 public:
  ~Exec() {}
};

}  // namespace removecontainer

class RemoveContainerCmdImpl
    : public RemoveContainerCmd,
      public AbstrDockerCmd<RemoveContainerCmd, std::string> {
 public:
  RemoveContainerCmdImpl(std::unique_ptr<removecontainer::Exec> exec,
                         std::string containerId);

  std::string exec() override;

  void close() override {}

  void withContainerId(std::string id) override;
  std::string getContainerId() override;
  bool hasForceEnabled() const override { return m_force; }
  RemoveContainerCmd& withForce(bool force) override {
    m_force = force;
    return *this;
  }

  ~RemoveContainerCmdImpl() {}

private:
  bool m_force{false};
};  // namespace dockercpp::command
}

#endif /* INCLUDE_REMOVE_CONTAINER_CMD_HPP */
