#ifndef STATS_CONTAINER_CMD_HPP
#define STATS_CONTAINER_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

struct Stats {
    // Add statistics fields based on docker stats output
    nlohmann::json usage;
    std::string container_id;
    std::string name;
};

class StatsContainerCmd : public SynchDockerCmd<std::vector<Stats>>,
                         public std::enable_shared_from_this<StatsContainerCmd> {
 public:
  virtual std::string getContainerId() const = 0;
  virtual StatsContainerCmd& withContainerId(const std::string& id) = 0;
  virtual bool isNoStream() const = 0;
  virtual StatsContainerCmd& withNoStream(bool noStream) = 0;
};

namespace stats {
class Exec : public exec::DockerCmdSyncExec<StatsContainerCmd, std::vector<Stats>> {
 public:
  ~Exec() {}
};
}  // namespace stats

class StatsContainerCmdImpl : public StatsContainerCmd,
                            public AbstrDockerCmd<StatsContainerCmd, std::vector<Stats>> {
 public:
  explicit StatsContainerCmdImpl(std::unique_ptr<stats::Exec> exec);

  std::vector<Stats> exec() override;

  void close() override {}

  std::string getContainerId() const override;
  StatsContainerCmd& withContainerId(const std::string& id) override;
  bool isNoStream() const override;
  StatsContainerCmd& withNoStream(bool noStream) override;

  ~StatsContainerCmdImpl() {}

 private:
  std::string m_containerId;
  bool m_noStream;
};

}  // namespace dockercpp::command
#endif /* STATS_CONTAINER_CMD_HPP */
