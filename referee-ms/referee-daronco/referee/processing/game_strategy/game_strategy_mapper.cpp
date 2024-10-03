#include "referee/processing/game_strategy/game_strategy_mapper.h"

#include <protocols/common/game_command.pb.h>
#include <protocols/common/game_stage.pb.h>
#include <protocols/common/game_strategy.pb.h>

namespace referee {
namespace {
namespace rc {
using ::protocols::common::GameCommand;
using ::protocols::common::GameStrategy;
} // namespace rc
} // namespace

rc::GameStrategy
GameStrategyMapper::fromCommandAndStage(::protocols::common::GameCommand game_command,
                                        ::protocols::common::GameStage game_stage) {
  return rc::GameStrategy{};
}

} // namespace referee
