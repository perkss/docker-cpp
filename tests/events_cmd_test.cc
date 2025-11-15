#include <gtest/gtest.h>
#include <memory>
#include <chrono>
#include <thread>

#include "docker_client.hh"
#include "events_cmd.hh"
#include "events_cmd_exec.hh"
#include "create_container_cmd.hh"
#include "pull_image_cmd.hh"
#include "start_container_cmd.hh"
#include "stop_container_cmd.hh"
#include "remove_container_cmd.hh"
#include "remove_image_cmd.hh"

namespace dockercpp::command::test {

// Unit tests for EventsCmd
class EventsCmdUnitTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test environment
    }

    void TearDown() override {
        // Clean up after each test
    }
};

TEST_F(EventsCmdUnitTest, TestEventsCmdWithSince) {
    auto eventsExec = std::make_unique<command::exec::EventsCmdExec>();
    auto cmd = std::make_shared<command::EventsCmdImpl>(std::move(eventsExec));
 
    int64_t testSince = 1234567890;
    cmd->withSince(testSince);

    EXPECT_EQ(cmd->getSince(), testSince);
}

TEST_F(EventsCmdUnitTest, TestEventsCmdWithUntil) {
    auto eventsExec = std::make_unique<command::exec::EventsCmdExec>();
    auto cmd = std::make_shared<command::EventsCmdImpl>(std::move(eventsExec));
    
    int64_t testUntil = 1234567890;
    cmd->withUntil(testUntil);

    EXPECT_EQ(cmd->getUntil(), testUntil);
}

TEST_F(EventsCmdUnitTest, TestEventsCmdChaining) {
    auto eventsExec = std::make_unique<command::exec::EventsCmdExec>();
    auto cmd = std::make_shared<command::EventsCmdImpl>(std::move(eventsExec));
    
    int64_t testSince = 1234567890;
    int64_t testUntil = 2234567890;

    cmd->withSince(testSince).withUntil(testUntil);

    EXPECT_EQ(cmd->getSince(), testSince);
    EXPECT_EQ(cmd->getUntil(), testUntil);
}

// Integration tests for EventsCmd
class EventsCmdIT : public ::testing::Test {
protected:
    void SetUp() override {
        dockerClient = std::make_unique<DockerClient>();
    }

    void TearDown() override {
        dockerClient.reset();
    }

    std::unique_ptr<DockerClient> dockerClient;
};

TEST_F(EventsCmdIT, testEventStreamTimeBound) {
    // Get the current time for since
    int64_t since = std::time(nullptr);

    // Pull an image
    dockerClient->pullImageCmd("busybox")
        ->withTag("1.36")
        .exec();

    // Create a container
    auto createResponse = dockerClient->createContainerCmd("busybox:1.36")
        ->withCmd(std::vector<std::string>{"top"})
        .withName("test-events")
        .exec();

    std::string containerId = createResponse.id;

    // Start container
    dockerClient->startContainerCmd(containerId)->exec();

    // Stop container
    dockerClient->stopContainerCmd(containerId)->exec();

    // Remove container
    dockerClient->removeContainerCmd(containerId)
        ->withForce(true)
        .exec();

    // Remove image
    dockerClient->removeImageCmd("busybox:1.36")->exec();

    // Get events until now
    int64_t until = std::time(nullptr);

    auto events = dockerClient->eventsCmd()
        ->withSince(since)
        .withUntil(until)
        .exec();

    // Verify we got the expected events
    bool foundPull = false;
    bool foundCreate = false;
    bool foundStart = false;
    bool foundStop = false;
    bool foundDestroy = false;
    bool foundDelete = false;

    for (const auto& event : events) {
        if (event.type == "image" && event.action == "pull") {
            foundPull = true;
        } else if (event.type == "container" && event.action == "create") {
            foundCreate = true;
            EXPECT_EQ(event.actor.attributes.at("name"), "test-events");
        } else if (event.type == "container" && event.action == "start") {
            foundStart = true;
        } else if (event.type == "container" && event.action == "stop") {
            foundStop = true;
        } else if (event.type == "container" && event.action == "destroy") {
            foundDestroy = true;
        } else if (event.type == "container" && event.action == "delete") {
            foundDelete = true;
        }
    }

    EXPECT_TRUE(foundPull) << "Should have found image pull event";
    EXPECT_TRUE(foundCreate) << "Should have found container create event";
    EXPECT_TRUE(foundStart) << "Should have found container start event";
    EXPECT_TRUE(foundStop) << "Should have found container stop event";
    EXPECT_TRUE(foundDestroy) << "Should have found container destroy event";
    EXPECT_TRUE(foundDelete) << "Should have found container delete event";
}

TEST_F(EventsCmdIT, testEventStreamWithFilter) {
    // Get the current time for since
    int64_t since = std::time(nullptr);

    // Create container
    auto createResponse = dockerClient->createContainerCmd("busybox:1.36")
        ->withCmd(std::vector<std::string>{"top"})
        .withName("test-events-filtered")
        .exec();

    std::string containerId = createResponse.id;

    // Start container
    dockerClient->startContainerCmd(containerId)->exec();

    // Stop container
    dockerClient->stopContainerCmd(containerId)->exec();

    int64_t until = std::time(nullptr);

    // Get events with container filter
    auto events = dockerClient->eventsCmd()
        ->withSince(since)
        .withUntil(until)
        .withContainerFilter("test-events-filtered")
        .exec();

    // Should only get events for our container
    for (const auto& event : events) {
        EXPECT_EQ(event.type, "container");
        EXPECT_EQ(event.actor.attributes.at("name"), "test-events-filtered");
    }

    // Cleanup
    dockerClient->removeContainerCmd(containerId)
        ->withForce(true)
        .exec();
}

TEST_F(EventsCmdIT, testEventStreamsMultipleFilters) {
    // Get the current time for since
    int64_t since = std::time(nullptr);

    // Create container with specific label
    auto createResponse = dockerClient->createContainerCmd("busybox:1.36")
        ->withCmd(std::vector<std::string>{"top"})
        .withName("test-events-multi-filter")
        .withLabel("test-label", "test-value")
        .exec();

    std::string containerId = createResponse.id;

    // Start container
    dockerClient->startContainerCmd(containerId)->exec();

    // Stop container
    dockerClient->stopContainerCmd(containerId)->exec();

    int64_t until = std::time(nullptr);

    // Get events with multiple filters
    auto events = dockerClient->eventsCmd()
        ->withSince(since)
        .withUntil(until)
        .withContainerFilter("test-events-multi-filter")
        .withLabelFilter("test-label=test-value")
        .withTypeFilter("container")
        .exec();

    EXPECT_FALSE(events.empty());

    // Verify all events match our filters
    for (const auto& event : events) {
        EXPECT_EQ(event.type, "container");
        EXPECT_EQ(event.actor.attributes.at("name"), "test-events-multi-filter");
        EXPECT_EQ(event.actor.attributes.at("test-label"), "test-value");
    }

    // Cleanup
    dockerClient->removeContainerCmd(containerId)
        ->withForce(true)
        .exec();
}

} // namespace dockercpp::command::test

