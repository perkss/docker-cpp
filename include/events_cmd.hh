#ifndef EVENTS_CMD_HPP
#define EVENTS_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

struct DockerEvent {
    std::string type;
    std::string action;
    std::string id;
    std::string from;
    int64_t time;
    int64_t timeNano;
    nlohmann::json actor;
};

class EventsCmd : public SynchDockerCmd<std::vector<DockerEvent>>,
                 public std::enable_shared_from_this<EventsCmd> {
 public:
  virtual int64_t getSince() const = 0;
  virtual int64_t getUntil() const = 0;
  virtual EventsCmd& withSince(int64_t since) = 0;
  virtual EventsCmd& withUntil(int64_t until) = 0;
};

namespace events {
class Exec : public exec::DockerCmdSyncExec<EventsCmd, std::vector<DockerEvent>> {
 public:
  ~Exec() {}
};
}  // namespace events

class EventsCmdImpl : public EventsCmd,
                     public AbstrDockerCmd<EventsCmd, std::vector<DockerEvent>> {
 public:
  explicit EventsCmdImpl(std::unique_ptr<events::Exec> exec);

  std::vector<DockerEvent> exec() override;

  void close() override {}

  int64_t getSince() const override;
  int64_t getUntil() const override;
  EventsCmd& withSince(int64_t since) override;
  EventsCmd& withUntil(int64_t until) override;

  ~EventsCmdImpl() {}

 private:
  int64_t m_since;
  int64_t m_until;
};

}  // namespace dockercpp::command
#endif /* EVENTS_CMD_HPP */
