#include <gtest/gtest.h>
#include <memory>

#include "stats_container_cmd.hh"
#include "docker_client.hh"

using namespace dockercpp::command;

class StatsContainerCmdTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test environment
    }

    void TearDown() override {
        // Clean up after each test
    }
};

// TEST_F(StatsContainerCmdTest, TestStatsContainerCmdBasicProperties) {
//     std::unique_ptr<stats::Exec> exec = std::make_unique<stats::Exec>();
//     StatsContainerCmdImpl cmd(std::move(exec));

//     std::string testContainerId = "test_container_123";
//     cmd.withContainerId(testContainerId);

//     EXPECT_EQ(cmd.getContainerId(), testContainerId);
// }

// TEST_F(StatsContainerCmdTest, TestStatsContainerCmdNoStream) {
//     std::unique_ptr<stats::Exec> exec = std::make_unique<stats::Exec>();
//     StatsContainerCmdImpl cmd(std::move(exec));

//     // Test default value
//     EXPECT_FALSE(cmd.isNoStream());

//     // Test setting value
//     cmd.withNoStream(true);
//     EXPECT_TRUE(cmd.isNoStream());
// }

// TEST_F(StatsContainerCmdTest, TestStatsContainerCmdChaining) {
//     std::unique_ptr<stats::Exec> exec = std::make_unique<stats::Exec>();
//     StatsContainerCmdImpl cmd(std::move(exec));

//     std::string testContainerId = "test_container_123";
//     cmd.withContainerId(testContainerId).withNoStream(true);

//     EXPECT_EQ(cmd.getContainerId(), testContainerId);
//     EXPECT_TRUE(cmd.isNoStream());
// }
