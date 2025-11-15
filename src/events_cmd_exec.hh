#ifndef EVENTS_CMD_EXEC_HH
#define EVENTS_CMD_EXEC_HH

#include <memory>
#include <nlohmann/json.hpp>
#include <vector>

#include "abstr_sync_docker_cmd_exec.hh"
#include "events_cmd.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

class EventsCmdExec : public AbstrSyncDockerCmdExec<EventsCmd, std::vector<DockerEvent>>,
                     public events::Exec {
 public:
  EventsCmdExec();

  std::vector<DockerEvent> execute(std::shared_ptr<EventsCmd> command) override;
  std::vector<DockerEvent> exec(std::shared_ptr<EventsCmd> command) override;

 private:
  void from_json(const nlohmann::json& j, DockerEvent& event);
  nlohmann::json buildFilterJson(const std::vector<std::string>& filters);
};

}  // namespace dockercpp::command::exec

#endif  // EVENTS_CMD_EXEC_HH
