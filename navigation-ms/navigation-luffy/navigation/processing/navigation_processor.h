#ifndef NAVIGATION_PROCESSING_NAVIGATION_PROCESSOR_H
#define NAVIGATION_PROCESSING_NAVIGATION_PROCESSOR_H

#include "../messaging/receiver/payload.h"
#include "motion_parser/go_to_point_parser.h"
#include "motion_parser/rotate_in_point_parser.h"
#include "motion_parser/rotate_on_self_parser.h"

#include <optional>
#include <protocols/navigation/navigation.pb.h>

namespace navigation {

class INavigationProcessor {
 public:
  INavigationProcessor() = default;

  INavigationProcessor(const INavigationProcessor&) = delete;
  INavigationProcessor& operator=(const INavigationProcessor&) = delete;
  INavigationProcessor(INavigationProcessor&&) = default;
  INavigationProcessor& operator=(INavigationProcessor&&) = default;

  virtual ~INavigationProcessor() = default;

  virtual std::optional<::protocols::navigation::Navigation>
  process(std::span<const Payload> payloads) = 0;
};

class NavigationProcessor : public INavigationProcessor {
 public:
  NavigationProcessor(std::unique_ptr<GoToPointParser> go_to_point_parser,
                      std::unique_ptr<RotateInPointParser> rotate_in_point_parser,
                      std::unique_ptr<RotateOnSelfParser> rotate_on_self_parser);

  std::optional<::protocols::navigation::Navigation>
  process(std::span<const Payload> payloads) override;

 private:
  std::unique_ptr<GoToPointParser> go_to_point_parser_;
  std::unique_ptr<RotateInPointParser> rotate_in_point_parser_;
  std::unique_ptr<RotateOnSelfParser> rotate_on_self_parser_;
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_DETECTION_PROCESSOR_H
