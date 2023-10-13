#include "inspect_image_response.hh"

namespace dockercpp::model {

void from_json(const nlohmann::json& j, InspectImageResponse& response) {
  j.at("Id").get_to(response.id);
}
}  // namespace dockercpp::model
