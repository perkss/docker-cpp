#ifndef INCLUDE_VERSION_CMD_HPP
#define INCLUDE_VERSION_CMD_HPP

#include <memory>
#include <string>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"
#include "version.hh"

namespace dockercpp::command {

class VersionCmd : public SynchDockerCmd<model::Version>,
                   public std::enable_shared_from_this<VersionCmd> {
 public:
  ~VersionCmd() override = default;
};

namespace version {
class Exec : public exec::DockerCmdSyncExec<VersionCmd, model::Version> {
 public:
  ~Exec() {}
};

}  // namespace version
class VersionCmdImpl : public VersionCmd,
                       public AbstrDockerCmd<VersionCmd, model::Version> {
 public:
  explicit VersionCmdImpl(std::unique_ptr<version::Exec> exec);

  model::Version exec() override;

  void close() override {}
  ~VersionCmdImpl() override = default;
};

}  // namespace dockercpp::command
#endif
