#ifndef REFEREE_PROCESSING_GAME_STRATEGY_MAPPER_H
#define REFEREE_PROCESSING_GAME_STRATEGY_MAPPER_H

#include <protocols/common/game_command.pb.h>
#include <protocols/common/game_stage.pb.h>
#include <protocols/common/game_strategy.pb.h>

namespace referee {

class IGameStrategyMapper {
 public:
  IGameStrategyMapper() = default;

  IGameStrategyMapper(const IGameStrategyMapper&) = delete;
  IGameStrategyMapper& operator=(const IGameStrategyMapper&) = delete;
  IGameStrategyMapper(IGameStrategyMapper&&) = default;
  IGameStrategyMapper& operator=(IGameStrategyMapper&&) = default;

  virtual ~IGameStrategyMapper() = default;

  virtual ::protocols::common::GameStrategy
  fromCommandAndStage(::protocols::common::GameCommand game_command,
                      ::protocols::common::GameStage game_stage)
      = 0;
};

class GameStrategyMapper : public IGameStrategyMapper {
 public:
  ::protocols::common::GameStrategy
  fromCommandAndStage(::protocols::common::GameCommand game_command,
                      ::protocols::common::GameStage game_stage) override;
};

} // namespace referee

#endif // REFEREE_PROCESSING_GAME_STRATEGY_MAPPER_H
