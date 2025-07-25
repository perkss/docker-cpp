#include <gtest/gtest.h>
#include <memory>

#include "search_images_cmd.hh"
#include "docker_client.hh"

using namespace dockercpp::command;

class SearchImagesCmdTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test environment
    }

    void TearDown() override {
        // Clean up after each test
    }
};

// TEST_F(SearchImagesCmdTest, TestSearchImagesCmdWithTerm) {
//     std::unique_ptr<search::Exec> exec = std::make_unique<search::Exec>();
//     SearchImagesCmdImpl cmd(std::move(exec));

//     std::string testTerm = "nginx";
//     cmd.withTerm(testTerm);

//     EXPECT_EQ(cmd.getTerm(), testTerm);
// }

// TEST_F(SearchImagesCmdTest, TestSearchImagesCmdWithLimit) {
//     std::unique_ptr<search::Exec> exec = std::make_unique<search::Exec>();
//     SearchImagesCmdImpl cmd(std::move(exec));

//     int testLimit = 10;
//     cmd.withLimit(testLimit);

//     EXPECT_EQ(cmd.getLimit(), testLimit);
// }

// TEST_F(SearchImagesCmdTest, TestSearchImagesCmdChaining) {
//     std::unique_ptr<search::Exec> exec = std::make_unique<search::Exec>();
//     SearchImagesCmdImpl cmd(std::move(exec));

//     std::string testTerm = "ubuntu";
//     int testLimit = 5;

//     cmd.withTerm(testTerm).withLimit(testLimit);

//     EXPECT_EQ(cmd.getTerm(), testTerm);
//     EXPECT_EQ(cmd.getLimit(), testLimit);
// }
