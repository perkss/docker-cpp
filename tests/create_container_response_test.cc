#include "create_container_response.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <nlohmann/json.hpp>
#include <string>

namespace dockercpp::model::test {

TEST(create_container_response_Test, fromJson) {
  auto id = "7cbb24cf0d61d92176e8ff08b0c5538d588735a56dbaa2045beaef0f2533793b";

  nlohmann::json response = nlohmann::json::parse(R"(
{"Id":"7cbb24cf0d61d92176e8ff08b0c5538d588735a56dbaa2045beaef0f2533793b","Warnings":[]}
)");

  CreateContainerResponse containerResponse =
      response.get<CreateContainerResponse>();

  ASSERT_EQ(id, containerResponse.id);
}

}  // namespace dockercpp::model::test
