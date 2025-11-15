#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <chrono>
#include <thread>

#include "docker_client.hh"
#include "remove_image_cmd.hh"
#include "pull_image_cmd.hh"
#include "inspect_image_cmd.hh"
#include "../src/remove_image_cmd_exec.hh"

namespace dockercpp::command::test {

// Unit tests for RemoveImageCmd
class RemoveImageCmdTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test environment
    }

    void TearDown() override {
        // Clean up after each test
    }
};

TEST_F(RemoveImageCmdTest, TestBasicRemoveImageCmd) {
    auto removeImageExec = std::make_unique<command::exec::RemoveImageCmdExec>();
    auto cmd = std::make_shared<command::RemoveImageCmdImpl>(
        std::move(removeImageExec), "test_image");

    EXPECT_EQ(cmd->getImageId(), "test_image");
}

// Integration tests for RemoveImageCmd
class RemoveImageCmdIT : public ::testing::Test {
protected:
    void SetUp() override {
        dockerClient = std::make_unique<DockerClient>();
        // Pull an image we know exists
        dockerClient->pullImageCmd("busybox")
            ->withTag("1.36")
            .exec();
    }

    void TearDown() override {
        try {
            // Try to remove the test image if it exists
            dockerClient->removeImageCmd("busybox:1.36")
                ->withForce(true)
                .exec();
        } catch (...) {
            // Ignore any errors during cleanup
        }
        dockerClient.reset();
    }

    std::unique_ptr<DockerClient> dockerClient;
};

TEST_F(RemoveImageCmdIT, testRemoveImage) {
    // Pull another tag of busybox to ensure we have it
    dockerClient->pullImageCmd("busybox")
        ->withTag("1.35")
        .exec();

    // Verify the image exists
    auto inspectResult = dockerClient->inspectImageCmd("busybox:1.35")->exec();
    EXPECT_FALSE(inspectResult.id.empty());

    // Remove the image
    ASSERT_NO_THROW(
        dockerClient->removeImageCmd("busybox:1.35")->exec()
    );

    // Verify the image is gone - should throw exception
    EXPECT_THROW(
        dockerClient->inspectImageCmd("busybox:1.35")->exec(),
        std::exception
    );
}

TEST_F(RemoveImageCmdIT, testRemoveNonExistingImage) {
    // Try to remove a non-existing image
    EXPECT_THROW(
        dockerClient->removeImageCmd("non_existing_image:latest")->exec(),
        std::exception
    );
}

TEST_F(RemoveImageCmdIT, testRemoveImageWithForce) {
    // Pull another tag of busybox
    dockerClient->pullImageCmd("busybox")
        ->withTag("1.34")
        .exec();

    // Force remove the image
    ASSERT_NO_THROW(
        dockerClient->removeImageCmd("busybox:1.34")
            ->withForce(true)
            .exec()
    );

    // Verify the image is gone
    EXPECT_THROW(
        dockerClient->inspectImageCmd("busybox:1.34")->exec(),
        std::exception
    );
}

}  // namespace dockercpp::command::test
