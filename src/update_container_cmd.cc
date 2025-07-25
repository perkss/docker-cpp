#include "update_container_cmd.hh"

namespace dockercpp::command {

UpdateContainerCmdImpl::UpdateContainerCmdImpl(std::unique_ptr<update::Exec> exec)
    : AbstrDockerCmd<UpdateContainerCmd, UpdateContainerResponse>(std::move(exec)),
      m_cpuShares(0),
      m_memory(0),
      m_memorySwap(0) {}

UpdateContainerResponse UpdateContainerCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

std::string UpdateContainerCmdImpl::getContainerId() const {
    return m_containerId;
}

UpdateContainerCmd& UpdateContainerCmdImpl::withContainerId(const std::string& id) {
    m_containerId = id;
    return *this;
}

int UpdateContainerCmdImpl::getCpuShares() const {
    return m_cpuShares;
}

UpdateContainerCmd& UpdateContainerCmdImpl::withCpuShares(int cpuShares) {
    m_cpuShares = cpuShares;
    return *this;
}

int64_t UpdateContainerCmdImpl::getMemory() const {
    return m_memory;
}

UpdateContainerCmd& UpdateContainerCmdImpl::withMemory(int64_t memory) {
    m_memory = memory;
    return *this;
}

int UpdateContainerCmdImpl::getMemorySwap() const {
    return m_memorySwap;
}

UpdateContainerCmd& UpdateContainerCmdImpl::withMemorySwap(int memorySwap) {
    m_memorySwap = memorySwap;
    return *this;
}

std::vector<std::string> UpdateContainerCmdImpl::getCpusetCpus() const {
    return m_cpusetCpus;
}

UpdateContainerCmd& UpdateContainerCmdImpl::withCpusetCpus(const std::vector<std::string>& cpusetCpus) {
    m_cpusetCpus = cpusetCpus;
    return *this;
}

}
