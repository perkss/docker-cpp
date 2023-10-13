#ifndef SRC_ABSTR_SYNC_DOCKER_CMD_EXEC_HPP
#define SRC_ABSTR_SYNC_DOCKER_CMD_EXEC_HPP

#include <concepts>
#include <iostream>
#include <memory>
#include <type_traits>

#include "docker_client_config.hh"
#include "docker_cmd.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

template <class Type>
concept CheckType = std::is_base_of<DockerCmd, Type>::value;

template <CheckType CMD_T, typename RES_T>
class DockerCmdSyncExec {
 public:
  virtual RES_T exec(std::shared_ptr<CMD_T> command) = 0;

  virtual ~DockerCmdSyncExec(){};
};

class AbstrDockerCmdExec {
 public:
  ~AbstrDockerCmdExec() {}

 protected:
  std::unique_ptr<core::WebTarget> m_webTarget;
  std::unique_ptr<core::DockerClientConfig> m_dockerClientConfig;
};

template <CheckType CMD_T, typename RES_T>
class AbstrSyncDockerCmdExec : public AbstrDockerCmdExec,
                               public DockerCmdSyncExec<CMD_T, RES_T> {
 public:
    virtual RES_T exec(std::shared_ptr<CMD_T> command) = 0;

  ~AbstrSyncDockerCmdExec(){};

 protected:
  virtual RES_T execute(std::shared_ptr<CMD_T> command) = 0;
};

}  // namespace dockercpp::command::exec

#endif /* SRC_ABSTR_SYNC_DOCKER_CMD_EXEC_HPP */
