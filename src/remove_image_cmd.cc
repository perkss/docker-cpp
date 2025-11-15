#include "remove_image_cmd.hh"

namespace dockercpp::command {

RemoveImageCmdImpl::RemoveImageCmdImpl(std::unique_ptr<remove::Exec> exec,
                                       const std::string& id)
    : AbstrDockerCmd<RemoveImageCmd, std::string>(std::move(exec)), m_id(id) {}

std::string RemoveImageCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

std::string RemoveImageCmdImpl::getImageId() { return m_id; }

bool m_force{false};
bool m_noPrune{false};

bool RemoveImageCmdImpl::hasForcedEnabled() { return m_force; }

bool RemoveImageCmdImpl::hasNoPruneEnabled() { return m_noPrune; }

RemoveImageCmd& RemoveImageCmdImpl::withForce(bool force) { 
    m_force = force;
    return *this;
}

RemoveImageCmd& RemoveImageCmdImpl::withNoPrune(bool force) {
    m_noPrune = force;
    return *this;
}

}  // namespace dockercpp::command
