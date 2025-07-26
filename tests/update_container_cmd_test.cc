#include <gtest/gtest.h>
#include <memory>

#include "update_container_cmd.hh"
#include "update_container_cmd_exec.hh"
#include "docker_client.hh"

using namespace dockercpp::command;

class UpdateContainerCmdTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test environment
    }

    void TearDown() override {
        // Clean up after each test
    }
};

TEST_F(UpdateContainerCmdTest, TestUpdateContainerCmdBasicProperties) {
    std::unique_ptr<update::Exec> exec = std::make_unique<dockercpp::command::exec::UpdateContainerCmdExec>();
    UpdateContainerCmdImpl cmd(std::move(exec));

    std::string testContainerId = "test_container_123";
    cmd.withContainerId(testContainerId);

    EXPECT_EQ(cmd.getContainerId(), testContainerId);
}

TEST_F(UpdateContainerCmdTest, TestUpdateContainerCmdResourceLimits) {
    std::unique_ptr<update::Exec> exec = std::make_unique<dockercpp::command::exec::UpdateContainerCmdExec>();
    UpdateContainerCmdImpl cmd(std::move(exec));

    int testCpuShares = 512;
    int64_t testMemory = 1024 * 1024 * 1024; // 1GB
    int testMemorySwap = 2048;

    cmd.withCpuShares(testCpuShares)
       .withMemory(testMemory)
       .withMemorySwap(testMemorySwap);

    EXPECT_EQ(cmd.getCpuShares(), testCpuShares);
    EXPECT_EQ(cmd.getMemory(), testMemory);
    EXPECT_EQ(cmd.getMemorySwap(), testMemorySwap);
}

TEST_F(UpdateContainerCmdTest, TestUpdateContainerCmdCpuSet) {
    std::unique_ptr<update::Exec> exec = std::make_unique<dockercpp::command::exec::UpdateContainerCmdExec>();
    UpdateContainerCmdImpl cmd(std::move(exec));

    std::vector<std::string> testCpusetCpus = {"0", "1", "2"};
    cmd.withCpusetCpus(testCpusetCpus);

    EXPECT_EQ(cmd.getCpusetCpus(), testCpusetCpus);
}

TEST_F(UpdateContainerCmdTest, TestUpdateContainerCmdChaining) {
   std::unique_ptr<update::Exec> exec = std::make_unique<dockercpp::command::exec::UpdateContainerCmdExec>();
     UpdateContainerCmdImpl cmd(std::move(exec));

    std::string testContainerId = "test_container_123";
    int testCpuShares = 256;
    int64_t testMemory = 512 * 1024 * 1024;

    cmd.withContainerId(testContainerId)
       .withCpuShares(testCpuShares)
       .withMemory(testMemory);

    EXPECT_EQ(cmd.getContainerId(), testContainerId);
    EXPECT_EQ(cmd.getCpuShares(), testCpuShares);
    EXPECT_EQ(cmd.getMemory(), testMemory);
}
