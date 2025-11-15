#include "../src/curl_docker_http_client.hh"

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

#include "docker_client.hh"
#include "info.hh"
#include "version.hh"

namespace dockercpp::transport::test {

TEST(Curl_Docker_Client_Test, ping_ok) {
  dockercpp::transport::http::CurlDockerHttpClient client =
      dockercpp::transport::http::CurlDockerHttpClient::make()
          .withDockerHost("")
          .withConnectTimeout(10)
          .withReadTimeout(10);

  http::Request request = http::Request::make()
                              .withMethod(http::Request::Method::GET)
                              .withPath("_ping");

  http::Response response = client.execute(request);

  EXPECT_EQ(200, response.getStatusCode());
  EXPECT_EQ("OK", response.getBody());
}

TEST(Curl_Docker_Client_Test, client_ping_ok) {
  spdlog::info("running clientPingOk");

  dockercpp::DockerClient dockerclient;

  auto response = dockerclient.pingCmd()->exec();

  EXPECT_EQ("OK", response);

  spdlog::info("run clientPingOk");
}

TEST(Curl_Docker_Client_Test, client_version) {
  spdlog::info("running clientVersion");

  dockercpp::DockerClient dockerclient;

  auto response = dockerclient.versionCmd()->exec();

  spdlog::info("client version response");

  ASSERT_FALSE(response.apiVersion.empty());
}

TEST(Curl_Docker_Client_Test, pull_image) {
  dockercpp::DockerClient dockerclient;
  model::Info info = dockerclient.infoCmd()->exec();

  spdlog::info("client info {}", info.toString());

  spdlog::info("client info image count {}", info.images);

  auto testImage = "busybox:1.36";

  try {
    dockerclient.removeImageCmd(testImage)->exec();
  } catch (...) {
    // just ignore if doesnt exist
  }

  info = dockerclient.infoCmd()->exec();

  int imagecount = info.images;

  spdlog::info("client info {}", info.toString());

  spdlog::info("client info 2 image count {}", info.images);

  auto pulledImage =
      dockerclient.pullImageCmd(testImage)->withTag("1.36").exec();

  info = dockerclient.infoCmd()->exec();

  EXPECT_LE(imagecount, info.images);

  spdlog::info("client info {}", info.toString());

  spdlog::info("client info 2 image count {}", info.images);
}

TEST(Curl_Docker_Client_Test, start_and_stop_container) {
  spdlog::info("running createcontainer");

  dockercpp::DockerClient dockerclient;

  auto pulledImage =
      dockerclient.pullImageCmd("busybox")->withTag("1.36").exec();

  spdlog::info("Pulled image");

  auto response = dockerclient.createContainerCmd("busybox:1.36")
                      ->withName("testcase")
                      .withCmd(std::vector<std::string>{"sleep", "9999"})
                      .exec();

  spdlog::info("client version response");

  ASSERT_FALSE(response.id.empty());

  auto startcontainer = dockerclient.startContainerCmd(response.id)->exec();
  auto inspectcontainer = dockerclient.inspectContainerCmd(response.id)->exec();

  ASSERT_TRUE(inspectcontainer.state.running);

  auto stopcontainer = dockerclient.stopContainerCmd(response.id)->exec();

  auto inspectcontainerstopped =
      dockerclient.inspectContainerCmd(response.id)->exec();

  ASSERT_FALSE(inspectcontainerstopped.state.running);

  ASSERT_EQ(137, inspectcontainerstopped.state.exitCode);

  auto deletecontainer = dockerclient.removeContainerCmd(response.id)->exec();

  spdlog::info("delete");
  auto deleteimage = dockerclient.removeImageCmd("busybox:1.36")->exec();
}

}  // namespace dockercpp::transport::test
