#ifndef EXEC_CREATE_CMD_EXEC_HH
#define EXEC_CREATE_CMD_EXEC_HH

#include <memory>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "exec_create_cmd.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

class ExecCreateCmdExec : public AbstrSyncDockerCmdExec<ExecCreateCmd, ExecCreateResponse>,
                         public command::exec::CreateExec {
 public:
  ExecCreateCmdExec();

  ExecCreateResponse exec(std::shared_ptr<ExecCreateCmd> command) override;

 protected:
  ExecCreateResponse execute(std::shared_ptr<ExecCreateCmd> command);
};

}  // namespace dockercpp::command::exec

#endif  // EXEC_CREATE_CMD_EXEC_HH
