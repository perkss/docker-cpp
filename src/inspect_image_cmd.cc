#include "inspect_image_cmd.hh"

namespace dockercpp::command {

InspectImageCmdImpl::InspectImageCmdImpl(
    std::unique_ptr<inspectimage::Exec> exec, const std::string& imageId)
    : AbstrDockerCmd<InspectImageCmd, model::InspectImageResponse>(
          std::move(exec)),
      m_imageId(imageId) {}

model::InspectImageResponse InspectImageCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

std::string InspectImageCmdImpl::getImageId() { return m_imageId; }

}  // namespace dockercpp::command
