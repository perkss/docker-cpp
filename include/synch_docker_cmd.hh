#ifndef INCLUDE_SYNCH_DOCKER_CMD_HPP
#define INCLUDE_SYNCH_DOCKER_CMD_HPP

#include <spdlog/spdlog.h>

#include <memory>

#include "abstr_sync_docker_cmd_exec.hh"
#include "docker_cmd.hh"

namespace dockercpp::command {

template <typename RES_T>
class SynchDockerCmd : public DockerCmd {
 public:
  virtual RES_T exec() = 0;

  virtual ~SynchDockerCmd() = default;
};

template <typename T>
concept ConceptObject = std::is_base_of<DockerCmd, T>::value;

template <ConceptObject CMD_T, typename RES_T>
class AbstrDockerCmd : SynchDockerCmd<RES_T> {
 public:
  explicit AbstrDockerCmd(
      std::unique_ptr<exec::DockerCmdSyncExec<CMD_T, RES_T>> execution)
      : m_execution(std::move(execution)){};

  RES_T exec() override {
  }

  ~AbstrDockerCmd() {}

 protected:
  std::unique_ptr<exec::DockerCmdSyncExec<CMD_T, RES_T>> m_execution;
};

}  // namespace dockercpp::command

#endif /* INCLUDE_SYNCH_DOCKER_CMD_HPP */
