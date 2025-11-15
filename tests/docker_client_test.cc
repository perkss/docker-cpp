
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

#include "docker_client_config.hh"


namespace dockercpp::test {

TEST(Client_Test, BasicAssertions) {
  std::string username = "user";
  const auto password = "password";
  core::Builder builder;

  spdlog::info("Running test for client");

  core::DefaultDockerClientConfig config =
      core::DefaultDockerClientConfig::make()
          .withDockerHost(
              "https://user:pass@example.com:443/path/to/"
              "my%2dfile.txt?id=42&name=John%20Doe+Jingleheimer%2DSchmidt#page%"
              "20anchor")
          .withRegistryUsername(username)
          .withRegistryPassword(password);

  ASSERT_EQ(username, config.getRegistryUsername());
  ASSERT_EQ(password, config.getRegistryPassword());
}

}  // namespace dockercpp::test
