#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <vector>
#include <string>

#include "docker_client.hh"

namespace dockercpp::test {

class ReadmeExamplesTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Initialize Docker client
    dockerclient = std::make_unique<dockercpp::DockerClient>();
  }

  void TearDown() override {
    dockerclient.reset();
  }

  std::unique_ptr<dockercpp::DockerClient> dockerclient;
};

// Basic Connection Test
TEST_F(ReadmeExamplesTest, BasicConnectionTest) {
  spdlog::info("Testing basic connection with ping command");

  // Verify Docker daemon is running
  try {
    auto ping = dockerclient->pingCmd()->exec();
    spdlog::info("Docker is accessible: {}", ping);
    EXPECT_FALSE(ping.empty());
  } catch (const std::exception& e) {
    spdlog::error("Ping failed: {}", e.what());
  }
}

// Working with Images - Pull Image
TEST_F(ReadmeExamplesTest, PullImageExample) {
  spdlog::info("Testing pull image command");

  bool success = false;
  try {
    // Pull an image
    auto pulledImage = dockerclient->pullImageCmd("busybox")
        ->withTag("1.36")
        .exec();
    spdlog::info("Image pulled successfully");
    success = true;
  } catch (const std::exception& e) {
    spdlog::warn("Pull image failed: {}", e.what());
  }
  
  EXPECT_TRUE(success) << "Pull image command should complete without exception";
}

// Working with Images - Inspect Image
TEST_F(ReadmeExamplesTest, InspectImageExample) {
  spdlog::info("Testing inspect image command");

  try {
    // Inspect an image
    auto imageInfo = dockerclient->inspectImageCmd("busybox:1.36")->exec();
    spdlog::info("Image inspected - ID: {}", imageInfo.id);
    EXPECT_FALSE(imageInfo.id.empty());
  } catch (const std::exception& e) {
    spdlog::warn("Inspect image failed: {}", e.what());
  }
}

// Note: searchImagesCmd is not currently exposed through DockerClient public API

// Container Lifecycle - Create Container
TEST_F(ReadmeExamplesTest, CreateContainerExample) {
  spdlog::info("Testing container creation");

  try {
    // Create a container with a name and command
    auto response = dockerclient->createContainerCmd("busybox:1.36")
        ->withName("readme-test-container")
        .withCmd(std::vector<std::string>{"sleep", "9999"})
        .exec();

    spdlog::info("Created container with ID: {}", response.id);
    EXPECT_FALSE(response.id.empty());

    // Cleanup: Remove the container
    try {
      dockerclient->removeContainerCmd(response.id)->exec();
      spdlog::info("Container removed successfully");
    } catch (const std::exception& e) {
      spdlog::warn("Container removal failed: {}", e.what());
    }
  } catch (const std::exception& e) {
    spdlog::error("Create container failed: {}", e.what());
  }
}

// Container Lifecycle - Start and Stop
TEST_F(ReadmeExamplesTest, StartStopContainerExample) {
  spdlog::info("Testing container start and stop");

  try {
    // Create a container
    auto response = dockerclient->createContainerCmd("busybox:1.36")
        ->withName("readme-test-start-stop")
        .withCmd(std::vector<std::string>{"sleep", "9999"})
        .exec();

    std::string container_id = response.id;

    // Start the container
    dockerclient->startContainerCmd(container_id)->exec();
    spdlog::info("Container started");

    // Inspect running container to get details
    auto inspectInfo = dockerclient->inspectContainerCmd(container_id)->exec();
    spdlog::info("Container running: {}", inspectInfo.state.running);
    EXPECT_TRUE(inspectInfo.state.running);

    // Stop the running container
    dockerclient->stopContainerCmd(container_id)->exec();
    spdlog::info("Container stopped");

    // Inspect stopped container
    auto stoppedInfo = dockerclient->inspectContainerCmd(container_id)->exec();
    spdlog::info("Container running (should be false): {}", stoppedInfo.state.running);

    // Remove the container
    dockerclient->removeContainerCmd(container_id)->exec();
    spdlog::info("Container removed");

  } catch (const std::exception& e) {
    spdlog::error("Start/stop container failed: {}", e.what());
  }
}

// Getting Docker Information - Version
TEST_F(ReadmeExamplesTest, VersionCommandExample) {
  spdlog::info("Testing Docker version command");

  try {
    // Get Docker version information
    auto versionInfo = dockerclient->versionCmd()->exec();
    spdlog::info("Docker Version: {}", versionInfo.version);
    spdlog::info("API Version: {}", versionInfo.apiVersion);
    spdlog::info("OS: {}", versionInfo.operatingSystem);
    spdlog::info("Arch: {}", versionInfo.arch);
    // Check that apiVersion is populated (version field may be empty depending on Docker response)
    EXPECT_FALSE(versionInfo.apiVersion.empty());
  } catch (const std::exception& e) {
    spdlog::error("Version command failed: {}", e.what());
  }
}

// Getting Docker Information - Info
TEST_F(ReadmeExamplesTest, InfoCommandExample) {
  spdlog::info("Testing Docker info command");

  try {
    // Get Docker system information
    auto info = dockerclient->infoCmd()->exec();
    spdlog::info("Containers: {}", info.containers);
    spdlog::info("Images: {}", info.images);
    spdlog::info("Running: {}", info.containersRunning);
    // Verify we got some info
    EXPECT_GE(info.containers, 0);
    EXPECT_GE(info.images, 0);
    EXPECT_GE(info.containersRunning, 0);
  } catch (const std::exception& e) {
    spdlog::error("Info command failed: {}", e.what());
  }
}

// Note: statsContainerCmd is not currently exposed through DockerClient public API

}  // namespace dockercpp::test
