#include "decision/processing/messages/common/game_command/game_command_message.h"

#include <protocols/common/game_command.pb.h>
#include <protocols/referee/game_status.pb.h>

namespace decision {
// todo(fnap): implement

protocols::common::GameCommand::Halt GameCommandMessage::HaltMessage::toProto() const {
  return protocols::common::GameCommand::Halt{};
}

protocols::common::GameCommand::InGame GameCommandMessage::InGameMessage::toProto() const {
  return protocols::common::GameCommand::InGame{};
};
} // namespace decision
