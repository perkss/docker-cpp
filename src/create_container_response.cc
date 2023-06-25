#include "create_container_response.hh"

namespace dockercpp::model {

void from_json(const nlohmann::json& j, CreateContainerResponse& c) {
  j.at("Id").get_to(c.id);
}
}  // namespace dockercpp::model
