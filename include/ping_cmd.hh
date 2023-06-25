#ifndef INCLUDE_PING_CMD_HPP
#define INCLUDE_PING_CMD_HPP

#include <spdlog/spdlog.h>

#include <concepts>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

#include "abstr_sync_docker_cmd_exec.hh"
#include "docker_cmd.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

// Understand if the parent needs public or just use private
class PingCmd : public SynchDockerCmd<std::string>,
                public std::enable_shared_from_this<PingCmd> {
 public:
  ~PingCmd() {}
};

namespace ping {
class Exec : public exec::DockerCmdSyncExec<PingCmd, std::string> {
 public:
  ~Exec() {}
};

}  // namespace ping

class PingCmdImpl : public PingCmd,
                    public AbstrDockerCmd<PingCmd, std::string> {
 public:
  explicit PingCmdImpl(std::unique_ptr<ping::Exec> exec);

  std::string exec() override;

  void close() override {}
  ~PingCmdImpl() {}
};

}  // namespace dockercpp::command

#endif /* INCLUDE_PING_CMD_HPP */
