#include "../src/events_cmd_exec.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "events_cmd.hh"

namespace dockercpp::command::exec {

// TEST(EventsTest, create) {
//     auto eventsExec = std::make_unique<command::exec::EventsCmdExec>();

//     auto eventsCmd = std::make_shared<command::EventsCmdImpl>(std::move(eventsExec));
//     eventsCmd->withSince(1234567890)
//              .withUntil(2234567890);

//     auto result = eventsCmd->exec();
// }

}  // namespace dockercpp::command::exec
