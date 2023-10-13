#ifndef INCLUDE_INSPECT_IMAGE_RESPONSE_HPP
#define INCLUDE_INSPECT_IMAGE_RESPONSE_HPP

#include "docker_object.hh"

#include <string>

#include <nlohmann/json.hpp>

namespace dockercpp::model {

struct InspectImageResponse : public DockerObject {
    std::string id;
};

void from_json(const nlohmann::json& j, InspectImageResponse& response);

}


#endif /* INCLUDE_INSPECT_IMAGE_RESPONSE_HPP */
