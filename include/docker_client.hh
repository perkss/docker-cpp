#ifndef DOCKER_CLIENT_H
#define DOCKER_CLIENT_H

#include "create_container_cmd.hh"
#include "events_cmd.hh"
#include "info_cmd.hh"
#include "ping_cmd.hh"
#include "pull_image_cmd.hh"
#include "remove_image_cmd.hh"
#include "remove_container_cmd.hh"
#include "start_container_cmd.hh"
#include "stop_container_cmd.hh"
#include "inspect_container_cmd.hh"
#include "inspect_image_cmd.hh"
#include "version_cmd.hh"

namespace dockercpp {

class DockerClient {
 public:
  std::shared_ptr<command::PingCmd> pingCmd();

  std::shared_ptr<command::VersionCmd> versionCmd();

  std::shared_ptr<command::CreateContainerCmd> createContainerCmd(
      std::string image);

  std::shared_ptr<command::StartContainerCmd> startContainerCmd(
      std::string containerId);

  std::shared_ptr<command::StopContainerCmd> stopContainerCmd(
      std::string containerId);

  std::shared_ptr<command::InspectContainerCmd> inspectContainerCmd(
      std::string containerId);

  std::shared_ptr<command::PullImageCmd> pullImageCmd(std::string repository);

  std::shared_ptr<command::InfoCmd> infoCmd();

  std::shared_ptr<command::RemoveImageCmd> removeImageCmd(std::string image);

  std::shared_ptr<command::InspectImageCmd> inspectImageCmd(std::string image);

  std::shared_ptr<command::RemoveContainerCmd> removeContainerCmd(std::string id);

  std::shared_ptr<command::EventsCmd> eventsCmd();
};

};  // namespace dockercpp
#endif
