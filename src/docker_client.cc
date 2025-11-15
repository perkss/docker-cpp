#include "docker_client.hh"

#include <memory>

#include "create_container_cmd_exec.hh"
#include "info_cmd.hh"
#include "info_cmd_exec.hh"
#include "inspect_container_cmd_exec.hh"
#include "inspect_image_cmd_exec.hh"
#include "ping_cmd.hh"
#include "ping_cmd_exec.hh"
#include "pull_image_cmd.hh"
#include "pull_image_cmd_exec.hh"
#include "remove_container_cmd.hh"
#include "remove_container_cmd_exec.hh"
#include "remove_image_cmd.hh"
#include "remove_image_cmd_exec.hh"
#include "start_container_cmd.hh"
#include "start_container_cmd_exec.hh"
#include "stop_container_cmd_exec.hh"
#include "version_cmd.hh"
#include "version_cmd_exec.hh"
#include "events_cmd_exec.hh"

namespace dockercpp {

std::shared_ptr<command::PingCmd> DockerClient::pingCmd() {
  return std::make_shared<command::PingCmdImpl>(
      std::move(std::make_unique<command::exec::PingCmdExec>()));
}

std::shared_ptr<command::VersionCmd> DockerClient::versionCmd() {
  return std::make_shared<command::VersionCmdImpl>(
      std::move(std::make_unique<command::exec::VersionCmdExec>()));
}

std::shared_ptr<command::CreateContainerCmd> DockerClient::createContainerCmd(
    std::string image) {
  return std::make_shared<command::CreateContainerCmdImpl>(
      std::move(std::make_unique<command::exec::CreateContainerCmdExec>()),
      image);
}

std::shared_ptr<command::StartContainerCmd> DockerClient::startContainerCmd(
    std::string containerId) {
  return std::make_shared<command::StartContainerCmdImpl>(
      std::move(std::make_unique<command::exec::StartContainerCmdExec>()),
      containerId);
}

std::shared_ptr<command::StopContainerCmd> DockerClient::stopContainerCmd(
    std::string containerId) {
  return std::make_shared<command::StopContainerCmdImpl>(
      std::move(std::make_unique<command::exec::StopContainerCmdExec>()),
      containerId);
}

std::shared_ptr<command::InspectContainerCmd> DockerClient::inspectContainerCmd(
    std::string containerId) {
  return std::make_shared<command::InspectContainerCmdImpl>(
      std::move(std::make_unique<command::exec::InspectContainerCmdExec>()),
      containerId);
}

std::shared_ptr<command::PullImageCmd> DockerClient::pullImageCmd(
    std::string repository) {
  return std::make_shared<command::PullImageCmdImpl>(
      std::move(std::make_unique<command::exec::PullImageCmdExec>()),
      repository);
}

std::shared_ptr<command::InfoCmd> DockerClient::infoCmd() {
  return std::make_shared<command::InfoCmdImpl>(
      std::move(std::make_unique<command::exec::InfoCmdExec>()));
}

std::shared_ptr<command::RemoveImageCmd> DockerClient::removeImageCmd(
    std::string image) {
  return std::make_shared<command::RemoveImageCmdImpl>(
      std::move(std::make_unique<command::exec::RemoveImageCmdExec>()), image);
}

std::shared_ptr<command::InspectImageCmd> DockerClient::inspectImageCmd(
    std::string image) {
  return std::make_shared<command::InspectImageCmdImpl>(
      std::move(std::make_unique<command::exec::InspectImageCmdExec>()), image);
}

std::shared_ptr<command::RemoveContainerCmd> DockerClient::removeContainerCmd(
    std::string id) {
  return std::make_shared<command::RemoveContainerCmdImpl>(
      std::move(std::make_unique<command::exec::RemoveContainerCmdExec>()), id);
}

std::shared_ptr<command::EventsCmd> DockerClient::eventsCmd() {
  return std::make_shared<command::EventsCmdImpl>(
      std::move(std::make_unique<command::exec::EventsCmdExec>()));
}

}  // namespace dockercpp
