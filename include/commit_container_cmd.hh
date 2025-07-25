#ifndef COMMIT_CONTAINER_CMD_HPP
#define COMMIT_CONTAINER_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

class CommitContainerCmd : public SynchDockerCmd<std::string>,
                         public std::enable_shared_from_this<CommitContainerCmd> {
 public:
  virtual std::string getContainerId() = 0;
  virtual std::string getRepository() = 0;
};

namespace commitcontainer {
class Exec : public exec::DockerCmdSyncExec<CommitContainerCmd, std::string> {
 public:
  ~Exec() {}
};
}  // namespace commitcontainer

class CommitContainerCmdImpl : public CommitContainerCmd,
                             public AbstrDockerCmd<CommitContainerCmd, std::string> {
 public:
  explicit CommitContainerCmdImpl(std::unique_ptr<commitcontainer::Exec> exec,
                                const std::string& containerId,
                                const std::string& repository);

  std::string exec() override;

  void close() override {}

  std::string getContainerId() override;
  std::string getRepository() override;

  ~CommitContainerCmdImpl() {}

 private:
  std::string m_containerId;
  std::string m_repository;
};

}  // namespace dockercpp::command
#endif /* COMMIT_CONTAINER_CMD_HPP */
