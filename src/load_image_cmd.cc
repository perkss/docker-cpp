#include "load_image_cmd.hh"

namespace dockercpp::command {

LoadImageCmd::LoadImageCmd(const std::string& tarContents) : m_tar(tarContents) {}

std::string LoadImageCmd::getTarContents() { return m_tar; }

LoadImageCmdImpl::LoadImageCmdImpl(std::unique_ptr<load::Exec> exec,
                                   const std::string& tar)
    : AbstrDockerCmd<LoadImageCmd, std::string>(std::move(exec)), LoadImageCmd(tar), m_tar(tar) {}

std::string LoadImageCmdImpl::exec() { return m_execution->exec(shared_from_this()); }

void LoadImageCmdImpl::close() {}

LoadImageCmdImpl::~LoadImageCmdImpl() {}

}  // namespace dockercpp::command
