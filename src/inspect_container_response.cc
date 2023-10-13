#include "inspect_container_response.hh"

namespace dockercpp::model {

void from_json(const nlohmann::json& j, InspectContainerResponse& response) {
  j.at("Id").get_to(response.id);
  j.at("Created").get_to(response.created);
  j.at("Driver").get_to(response.driver);
  j.at("HostnamePath").get_to(response.hostnamePath);
  j.at("HostsPath").get_to(response.hostsPath);
  j.at("LogPath").get_to(response.logPath);
  j.at("MountLabel").get_to(response.mountLabel);
  j.at("Name").get_to(response.name);
  j.at("RestartCount").get_to(response.restartCount);
  j.at("Path").get_to(response.path);
  j.at("ProcessLabel").get_to(response.processLabel);
  j.at("State").get_to(response.state);
}

void from_json(const nlohmann::json& j, ContainerState& response) {
  j.at("Running").get_to(response.running);
  j.at("ExitCode").get_to(response.exitCode);
}

}  // namespace dockercpp::model
