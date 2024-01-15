#include "remove_image_cmd.hh"

namespace dockercpp::command {

RemoveImageCmdImpl::RemoveImageCmdImpl(std::unique_ptr<remove::Exec> exec,
                                       const std::string& id)
    : AbstrDockerCmd<RemoveImageCmd, std::string>(std::move(exec)), m_id(id) {}

std::string RemoveImageCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

std::string RemoveImageCmdImpl::getImageId() { return m_id; }

bool RemoveImageCmdImpl::hasForcedEnabled() { return false; }

bool RemoveImageCmdImpl::hasNoPruneEnabled() { return false; }

void RemoveImageCmdImpl::withForce(bool force) {}

void RemoveImageCmdImpl::withNoPrune(bool force) {}

}  // namespace dockercpp::command
