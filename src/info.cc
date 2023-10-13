#include "info.hh"

#include <nlohmann/json.hpp>
#include <sstream>

namespace dockercpp::model {

void from_json(const nlohmann::json& j, Info& info) {
  j.at("Images").get_to(info.images);
  j.at("Containers").get_to(info.containers);
  j.at("ContainersRunning").get_to(info.containersRunning);
  j.at("ContainersPaused").get_to(info.containersPaused);
  j.at("ContainersStopped").get_to(info.containersStopped);
}

std::string Info::toString() {
  std::stringstream ss;
  ss << (*this);
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Info& i) {
  return (os << "Images: " << i.images << std::endl
             << "containers: " << i.containers << std::endl
             << "containersRunning: " << i.containersRunning << std::endl
             << "containersPaused: " << i.containersPaused << std::endl
             << "containersStopped: " << i.containersStopped << std::endl);
}

}  // namespace dockercpp::model
