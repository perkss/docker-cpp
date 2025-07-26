#include <gtest/gtest.h>
#include <memory>
#include "events_cmd_exec.hh"

#include "events_cmd.hh"

namespace dockercpp::command::exec::test {

class EventsCmdTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test environment
    }

    void TearDown() override {
        // Clean up after each test
    }
};

TEST_F(EventsCmdTest, TestEventsCmdWithSince) {
    auto eventsExec = std::make_unique<command::exec::EventsCmdExec>();

    auto cmd = std::make_shared<command::EventsCmdImpl>(std::move(eventsExec));
 
    int64_t testSince = 1234567890;
    cmd->withSince(testSince);

    EXPECT_EQ(cmd->getSince(), testSince);
}

TEST_F(EventsCmdTest, TestEventsCmdWithUntil) {
    auto eventsExec = std::make_unique<command::exec::EventsCmdExec>();

    auto cmd = std::make_shared<command::EventsCmdImpl>(std::move(eventsExec));
 
   
    int64_t testUntil = 1234567890;
    cmd->withUntil(testUntil);

    EXPECT_EQ(cmd->getUntil(), testUntil);
}

TEST_F(EventsCmdTest, TestEventsCmdChaining) {
   auto eventsExec = std::make_unique<command::exec::EventsCmdExec>();

    auto cmd = std::make_shared<command::EventsCmdImpl>(std::move(eventsExec));
 
   
    int64_t testSince = 1234567890;
    int64_t testUntil = 2234567890;

    cmd->withSince(testSince).withUntil(testUntil);

    EXPECT_EQ(cmd->getSince(), testSince);
    EXPECT_EQ(cmd->getUntil(), testUntil);
}


}

