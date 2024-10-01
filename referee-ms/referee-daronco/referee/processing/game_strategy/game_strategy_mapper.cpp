#include "referee/processing/game_strategy/game_strategy_mapper.h"

#include <protocols/common/game_command.pb.h>
#include <protocols/common/game_strategy.pb.h>

namespace referee {
namespace {
namespace rc {
using ::protocols::common::GameCommand;
using ::protocols::common::GameStrategy;
}
} // namespace

rc::GameStrategy GameStrategyMapper::fromCommandAndStage(const ::protocols::common::GameCommand& game_command,
                                        const ::protocols::common::GameStage& game_stage) {
                                            return rc::GameStrategy{};
                                        }

} // namespace referee