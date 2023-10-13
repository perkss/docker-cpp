#ifndef INFO_H
#define INFO_H

#include "docker_object.hh"
#include <string>

#include <nlohmann/json.hpp>

namespace dockercpp::model {

class Info: model::DockerObject {
  public:

    std::string toString();

    int images = 0;

    int containers = 0;

    int containersRunning = 0;

    int containersPaused = 0;

    int containersStopped = 0;

    friend std::ostream& operator<<(std::ostream& os, const Info& i);
};

void from_json(const nlohmann::json& j, Info& info);

}

#endif
