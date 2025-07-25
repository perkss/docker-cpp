#include <gtest/gtest.h>
#include <memory>

#include "events_cmd.hh"
#include "docker_client.hh"

using namespace dockercpp::command;

class EventsCmdTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test environment
    }

    void TearDown() override {
        // Clean up after each test
    }
};

// TEST_F(EventsCmdTest, TestEventsCmdWithSince) {
//     std::unique_ptr<events::Exec> exec = std::make_unique<events::Exec>();
//     EventsCmdImpl cmd(std::move(exec));

//     int64_t testSince = 1234567890;
//     cmd.withSince(testSince);

//     EXPECT_EQ(cmd.getSince(), testSince);
// }

// TEST_F(EventsCmdTest, TestEventsCmdWithUntil) {
//     std::unique_ptr<events::Exec> exec = std::make_unique<events::Exec>();
//     EventsCmdImpl cmd(std::move(exec));

//     int64_t testUntil = 1234567890;
//     cmd.withUntil(testUntil);

//     EXPECT_EQ(cmd.getUntil(), testUntil);
// }

// TEST_F(EventsCmdTest, TestEventsCmdChaining) {
//     std::unique_ptr<events::Exec> exec = std::make_unique<events::Exec>();
//     EventsCmdImpl cmd(std::move(exec));

//     int64_t testSince = 1234567890;
//     int64_t testUntil = 2234567890;

//     cmd.withSince(testSince).withUntil(testUntil);

//     EXPECT_EQ(cmd.getSince(), testSince);
//     EXPECT_EQ(cmd.getUntil(), testUntil);
// }
