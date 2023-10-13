#ifndef SRC_VERSION_CMD_EXEC_HPP
#define SRC_VERSION_CMD_EXEC_HPP

#include <string>

#include "abstr_sync_docker_cmd_exec.hh"
#include "version.hh"
#include "version_cmd.hh"

namespace dockercpp::command::exec {

class VersionCmdExec
    : public AbstrSyncDockerCmdExec<dockercpp::command::VersionCmd,
                                    model::Version>,
      public version::Exec {
 public:
  VersionCmdExec();
  model::Version exec(
      std::shared_ptr<dockercpp::command::VersionCmd> command) override;

  ~VersionCmdExec() {}

 protected:
  model::Version execute(
      std::shared_ptr<dockercpp::command::VersionCmd> command) override;
};

}  // namespace dockercpp::command::exec

#endif /* SRC_VERSION_CMD_EXEC_HPP */
