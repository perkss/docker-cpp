#ifndef UPDATE_CONTAINER_CMD_HPP
#define UPDATE_CONTAINER_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

struct UpdateContainerResponse {
    nlohmann::json warnings;
};

class UpdateContainerCmd : public SynchDockerCmd<UpdateContainerResponse>,
                         public std::enable_shared_from_this<UpdateContainerCmd> {
 public:
  virtual std::string getContainerId() const = 0;
  virtual UpdateContainerCmd& withContainerId(const std::string& id) = 0;
  virtual int getCpuShares() const = 0;
  virtual UpdateContainerCmd& withCpuShares(int cpuShares) = 0;
  virtual int64_t getMemory() const = 0;
  virtual UpdateContainerCmd& withMemory(int64_t memory) = 0;
  virtual int getMemorySwap() const = 0;
  virtual UpdateContainerCmd& withMemorySwap(int memorySwap) = 0;
  virtual std::vector<std::string> getCpusetCpus() const = 0;
  virtual UpdateContainerCmd& withCpusetCpus(const std::vector<std::string>& cpusetCpus) = 0;
};

namespace update {
class Exec : public exec::DockerCmdSyncExec<UpdateContainerCmd, UpdateContainerResponse> {
 public:
  ~Exec() {}
};
}  // namespace update

class UpdateContainerCmdImpl : public UpdateContainerCmd,
                            public AbstrDockerCmd<UpdateContainerCmd, UpdateContainerResponse> {
 public:
  explicit UpdateContainerCmdImpl(std::unique_ptr<update::Exec> exec);

  UpdateContainerResponse exec() override;

  void close() override {}

  std::string getContainerId() const override;
  UpdateContainerCmd& withContainerId(const std::string& id) override;
  int getCpuShares() const override;
  UpdateContainerCmd& withCpuShares(int cpuShares) override;
  int64_t getMemory() const override;
  UpdateContainerCmd& withMemory(int64_t memory) override;
  int getMemorySwap() const override;
  UpdateContainerCmd& withMemorySwap(int memorySwap) override;
  std::vector<std::string> getCpusetCpus() const override;
  UpdateContainerCmd& withCpusetCpus(const std::vector<std::string>& cpusetCpus) override;

  ~UpdateContainerCmdImpl() {}

 private:
  std::string m_containerId;
  int m_cpuShares;
  int64_t m_memory;
  int m_memorySwap;
  std::vector<std::string> m_cpusetCpus;
};

}  // namespace dockercpp::command
#endif /* UPDATE_CONTAINER_CMD_HPP */
