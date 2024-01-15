#ifndef SRC_INFO_CMD_EXEC_HPP
#define SRC_INFO_CMD_EXEC_HPP

#include <string>

#include "abstr_sync_docker_cmd_exec.hh"
#include "info_cmd.hh"

namespace dockercpp::command::exec {

class InfoCmdExec : public AbstrSyncDockerCmdExec<dockercpp::command::InfoCmd,
                                                  dockercpp::model::Info>,
                    public info::Exec {
 public:
  InfoCmdExec();
  dockercpp::model::Info exec(
      std::shared_ptr<dockercpp::command::InfoCmd> command) override;

  ~InfoCmdExec() {}

 protected:
  dockercpp::model::Info execute(
      std::shared_ptr<dockercpp::command::InfoCmd> command) override;
};
}  // namespace dockercpp::command::exec

#endif /* SRC_INFO_CMD_EXEC_HPP */
