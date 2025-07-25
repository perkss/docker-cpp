#include "../src/exec_create_cmd_exec.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "exec_create_cmd.hh"

namespace dockercpp::command::exec {

TEST(ExecCreateTest, create) {
    // auto execCreateExec = std::make_unique<command::exec::ExecCreateCmdExec>();

    // auto execCreateCmd = std::make_shared<command::ExecCreateCmdImpl>(std::move(execCreateExec));
    // execCreateCmd->withContainerId("test_container_123")
    //             .withCmd({"/bin/bash", "-c", "echo hello"})
    //             .withUser("testuser")
    //             .withAttachStdin(true)
    //             .withTty(true);

    // auto result = execCreateCmd->exec();
}

}  // namespace dockercpp::command::exec
