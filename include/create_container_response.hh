#ifndef INCLUDE_CREATE_CONTAINER_RESPONSE_HPP
#define INCLUDE_CREATE_CONTAINER_RESPONSE_HPP

#include "docker_object.hh"

#include <nlohmann/json.hpp>

// https://github.com/docker-java/docker-java/blob/main/docker-java-api/src/main/java/com/github/dockerjava/api/command/CreateContainerResponse.java
namespace dockercpp::model {
struct CreateContainerResponse : public DockerObject {
 public:
  std::string id;
};

void from_json(const nlohmann::json& j, CreateContainerResponse& version);
}  // namespace dockercpp::model

#endif /* INCLUDE_CREATE_CONTAINER_RESPONSE_HPP */
