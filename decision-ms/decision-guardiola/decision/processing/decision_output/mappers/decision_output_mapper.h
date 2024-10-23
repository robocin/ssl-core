#ifndef DECISION_PROCESSING_DECISION_OUTPUT_MAPPER_DECISION_OUTPUT_MAPPER_H
#define DECISION_PROCESSING_DECISION_OUTPUT_MAPPER_DECISION_OUTPUT_MAPPER_H

#include <protocols/decision/decision.pb.h>
#include <protocols/perception/detection.pb.h>

namespace decision {

class IDecisionOutputMapper {
 public:
  IDecisionOutputMapper() = default;

  IDecisionOutputMapper(const IDecisionOutputMapper&) = delete;
  IDecisionOutputMapper& operator=(const IDecisionOutputMapper&) = delete;
  IDecisionOutputMapper(IDecisionOutputMapper&&) = default;
  IDecisionOutputMapper& operator=(IDecisionOutputMapper&&) = default;

  virtual ~IDecisionOutputMapper() = default;

  virtual ::protocols::decision::Decision map() = 0;
};

/**
 * @class DecisionOutputMapper
 * @brief Creates Decision from ....
 *
 * The DecisionMapper class provides static methods to create
 * a Decision object and their components from ...
 */
class DecisionOutputMapper : public IDecisionOutputMapper {
 public:
  DecisionOutputMapper() = default;

  /**
   * @brief Creates an Decision .
   * @param PARAM_TODO The param to be processed.
   * @return A Decision object.
   *
   * This method takes an PARAM_TODO and creates an Decision object
   * , which includes the processed robot information, id and target.
   */
  ::protocols::decision::Decision map() override;
};

} // namespace decision

#endif // DECISION_PROCESSING_DECISION_OUTPUT_MAPPER_DECISION_OUTPUT_MAPPER_H
