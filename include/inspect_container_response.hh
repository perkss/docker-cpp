#ifndef INCLUDE_INSPECT_CONTAINER_RESPONSE_HPP
#define INCLUDE_INSPECT_CONTAINER_RESPONSE_HPP

#include "docker_object.hh"

#include <string>

#include <nlohmann/json.hpp>

namespace dockercpp::model {

struct ContainerState : public DockerObject {
  bool running;
    long exitCode;

};

struct InspectContainerResponse : public DockerObject {
  public:
    std::string id;
    std::string created;
    std::string driver;
    std::string execDriver;
    std::string hostnamePath;
    std::string hostsPath;
    std::string logPath;
    std::string imageId;
    std::string mountLabel;
    std::string name;
    int restartCount;
    std::string path;
    std::string processLabel;
    std::string resolvConfPath;
    std::vector<std::string> execIds;
    ContainerState state;
};

void from_json(const nlohmann::json& j, InspectContainerResponse& response);
void from_json(const nlohmann::json& j, ContainerState& response);

}

#endif /* INCLUDE_INSPECT_CONTAINER_RESPONSE_HPP */
