#ifndef VERSION_H
#define VERSION_H

#include "docker_object.hh"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace dockercpp::model {

struct Version : DockerObject {
  std::string apiVersion;
  std::string arch;
  std::string goVersion;
  std::string gitCommit;
  std::string kernelVersion;
  std::string operatingSystem;
  std::string version;
  std::string buildTime;
  bool experimental;
  std::string minAPIVersion;
  std::string platform;
  std::vector<std::string> components;
};

void from_json(const nlohmann::json& j, Version& version);
}  // namespace dockercpp::model

#endif
