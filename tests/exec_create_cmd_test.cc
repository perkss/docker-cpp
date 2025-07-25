#include <gtest/gtest.h>
#include <memory>

#include "exec_create_cmd.hh"
#include "docker_client.hh"

using namespace dockercpp::command;

class ExecCreateCmdTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test environment
    }

    void TearDown() override {
        // Clean up after each test
    }
};

TEST_F(ExecCreateCmdTest, TestExecCreateCmdBasicProperties) {
    std::unique_ptr<exec::CreateExec> exec = std::make_unique<exec::CreateExec>();
    ExecCreateCmdImpl cmd(std::move(exec));

    std::string testContainerId = "test_container_123";
    std::vector<std::string> testCmd = {"/bin/bash", "-c", "echo hello"};
    std::string testUser = "testuser";

    cmd.withContainerId(testContainerId)
       .withCmd(testCmd)
       .withUser(testUser);

    EXPECT_EQ(cmd.getContainerId(), testContainerId);
    EXPECT_EQ(cmd.getCmd(), testCmd);
    EXPECT_EQ(cmd.getUser(), testUser);
}

TEST_F(ExecCreateCmdTest, TestExecCreateCmdFlags) {
    std::unique_ptr<exec::CreateExec> exec = std::make_unique<exec::CreateExec>();
    ExecCreateCmdImpl cmd(std::move(exec));

    // Test default values
    EXPECT_FALSE(cmd.isAttachStdin());
    EXPECT_TRUE(cmd.isAttachStdout());
    EXPECT_TRUE(cmd.isAttachStderr());
    EXPECT_FALSE(cmd.isTty());
    EXPECT_FALSE(cmd.isPrivileged());

    // Test setting values
    cmd.withAttachStdin(true)
       .withAttachStdout(false)
       .withAttachStderr(false)
       .withTty(true)
       .withPrivileged(true);

    EXPECT_TRUE(cmd.isAttachStdin());
    EXPECT_FALSE(cmd.isAttachStdout());
    EXPECT_FALSE(cmd.isAttachStderr());
    EXPECT_TRUE(cmd.isTty());
    EXPECT_TRUE(cmd.isPrivileged());
}
