#ifndef REFEREE_PROCESSING_PARSER_PARSER_H
#define REFEREE_PROCESSING_PARSER_PARSER_H

#include <protocols/common/game_command.pb.h>
#include <protocols/common/game_stage.pb.h>

namespace referee {

class IParser {
 public:
  IParser() = default;

  IParser(const IParser&) = delete;
  IParser& operator=(const IParser&) = delete;
  IParser(IParser&&) = default;
  IParser& operator=(IParser&&) = default;

  virtual ~IParser() = default;

  ::protocols::common::GameState parse(const ::protocols::common::GameCommand& game_command, const ::protocols::common::GameStage& game_stage)
    = 0;
};

} // namespace referee

#endif // REFEREE_PROCESSING_PARSER_PARSER_H