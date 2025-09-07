#ifndef EVENTS_CMD_HPP
#define EVENTS_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

struct DockerActor {
    std::string id;
    std::map<std::string, std::string> attributes;
};

struct DockerEvent {
    std::string type;
    std::string action;
    std::string id;
    std::string from;
    int64_t time;
    int64_t timeNano;
    DockerActor actor;
    std::map<std::string, std::string> labels;
    std::string status;
    std::string scope;
};

class EventsCmd : public SynchDockerCmd<std::vector<DockerEvent>>,
                 public std::enable_shared_from_this<EventsCmd> {
 public:
  virtual int64_t getSince() const = 0;
  virtual int64_t getUntil() const = 0;
  virtual std::vector<std::string> getFilters() const = 0;

  virtual EventsCmd& withSince(int64_t since) = 0;
  virtual EventsCmd& withUntil(int64_t until) = 0;
  virtual EventsCmd& withContainerFilter(const std::string& container) = 0;
  virtual EventsCmd& withEventFilter(const std::string& event) = 0;
  virtual EventsCmd& withImageFilter(const std::string& image) = 0;
  virtual EventsCmd& withLabelFilter(const std::string& label) = 0;
  virtual EventsCmd& withVolumeFilter(const std::string& volume) = 0;
  virtual EventsCmd& withNetworkFilter(const std::string& network) = 0;
  virtual EventsCmd& withDaemonFilter(const std::string& daemon) = 0;
  virtual EventsCmd& withTypeFilter(const std::string& type) = 0;
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

  int64_t getSince() const override { return m_since; }
  int64_t getUntil() const override { return m_until; }
  std::vector<std::string> getFilters() const override;

  EventsCmd& withSince(int64_t since) override {
    m_since = since;
    return *this;
  }

  EventsCmd& withUntil(int64_t until) override {
    m_until = until;
    return *this;
  }

  EventsCmd& withContainerFilter(const std::string& container) override {
    return withFilter("container", container);
  }

  EventsCmd& withEventFilter(const std::string& event) override {
    return withFilter("event", event);
  }

  EventsCmd& withImageFilter(const std::string& image) override {
    return withFilter("image", image);
  }

  EventsCmd& withLabelFilter(const std::string& label) override {
    return withFilter("label", label);
  }

  EventsCmd& withVolumeFilter(const std::string& volume) override {
    return withFilter("volume", volume);
  }

  EventsCmd& withNetworkFilter(const std::string& network) override {
    return withFilter("network", network);
  }

  EventsCmd& withDaemonFilter(const std::string& daemon) override {
    return withFilter("daemon", daemon);
  }

  EventsCmd& withTypeFilter(const std::string& type) override {
    return withFilter("type", type);
  }

  ~EventsCmdImpl() = default;

 private:
  int64_t m_since{0};
  int64_t m_until{0};
  std::map<std::string, std::vector<std::string>> m_filters;
  
  EventsCmd& withFilter(const std::string& key, const std::string& value) {
    if (!m_filters.contains(key)) {
      m_filters[key] = std::vector<std::string>();
    }
    m_filters[key].push_back(value);
    return *this;
  }
};

}  // namespace dockercpp::command
#endif /* EVENTS_CMD_HPP */
