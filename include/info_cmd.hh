#ifndef INCLUDE_INFO_CMD_HPP
#define INCLUDE_INFO_CMD_HPP

#include <concepts>
#include <memory>
#include <string>

#include "info.hh"

#include "abstr_sync_docker_cmd_exec.hh"
#include "docker_cmd.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

// Understand if the parent needs public or just use private
class InfoCmd : public SynchDockerCmd<dockercpp::model::Info>,
                public std::enable_shared_from_this<InfoCmd> {
 public:
  ~InfoCmd() {}
};

namespace info {
class Exec : public exec::DockerCmdSyncExec<InfoCmd, dockercpp::model::Info> {
 public:
  ~Exec() {}
};

}  // namespace ping

class InfoCmdImpl : public InfoCmd,
                    public AbstrDockerCmd<InfoCmd, dockercpp::model::Info> {
 public:
  explicit InfoCmdImpl(std::unique_ptr<info::Exec> exec);

  dockercpp::model::Info exec() override;

  void close() override {}
  ~InfoCmdImpl() {}
};

}  // namespace dockercpp::command



#endif /* INCLUDE_INFO_CMD_HPP */
