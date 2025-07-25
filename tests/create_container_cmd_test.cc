#include "create_container_cmd.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "../src/create_container_cmd_exec.hh"

namespace dockercpp::command::test {

// TEST(create_container_cmd_Test, toJson) {
//   auto createContainerCmd = command::CreateContainerCmdImpl(
//       std::move(std::make_unique<command::exec::CreateContainerCmdExec>()),
//       "alpine");

//   createContainerCmd.withHost("local");

//   auto expectedResponse = nlohmann::json::parse(R"(
// {"Hostname":"local","Image":"alpine"}
// )");

//   nlohmann::json json = createContainerCmd.getRequest();

//   spdlog::info("Json {}", json.dump());

//   ASSERT_TRUE(json == expectedResponse);
// }
}  // namespace dockercpp::command::test
