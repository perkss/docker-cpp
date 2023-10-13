#include "pull_image_cmd.hh"

namespace dockercpp::command {

PullImageCmd& PullImageCmd::withTag(std::string tag) {
  m_tag = tag;
  return *this;
}

std::string PullImageCmd::getRepository() { return m_repository; }

std::string PullImageCmd::getTag() { return m_tag; }

std::string PullImageCmd::getRegistry() { return m_registry; }

std::string PullImageCmd::getPlatform() { return m_platform; }

PullImageCmd::PullImageCmd(const std::string& image) : m_repository(image) {}

PullImageCmdImpl::PullImageCmdImpl(std::unique_ptr<pull::Exec> exec,
                                   const std::string& image)
    : AbstrDockerCmd<PullImageCmd, std::string>(std::move(exec)),
      PullImageCmd(image) {}

std::string PullImageCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

void PullImageCmdImpl::close() {}

PullImageCmdImpl::~PullImageCmdImpl() {}

}  // namespace dockercpp::command
