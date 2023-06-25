#include "version.hh"

#include <nlohmann/json.hpp>

namespace dockercpp::model {

void from_json(const nlohmann::json& j, Version& version) {
  j.at("ApiVersion").get_to(version.apiVersion);
}
}  // namespace dockercpp::model
