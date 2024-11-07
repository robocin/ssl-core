#ifndef DECISION_PROCESSING_ROLE_IROLE_H
#define DECISION_PROCESSING_ROLE_IROLE_H

#include "decision/processing/messages/behavior/behavior_message.h"

namespace decision {

struct BehaviorCandidate {
  BehaviorMessage::BehaviorId behavior_id;
  float evaluation;
};

class IRole {
 public:
  IRole() = default;

  IRole(const IRole&) = delete;
  IRole& operator=(const IRole&) = delete;
  IRole(IRole&&) = default;
  IRole& operator=(IRole&&) = default;

  virtual ~IRole() = default;

  virtual std::vector<BehaviorCandidate> exec() = 0;
};

} // namespace decision

#endif // DECISION_PROCESSING_ROLE_IROLE_H
