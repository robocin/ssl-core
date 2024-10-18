#ifndef NAVIGATION_PROCESSING_NAVIGATION_PROCESSOR_H
#define NAVIGATION_PROCESSING_NAVIGATION_PROCESSOR_H

#include "navigation/messaging/receiver/payload.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <protocols/navigation/navigation.pb.h>
#include <robocin/detection_util/clock.h>
#include <robocin/parameters/parameters.h>

namespace navigation {

class INavigationProcessor {
 public:
  INavigationProcessor() = default;

  INavigationProcessor(const INavigationProcessor&) = delete;
  INavigationProcessor& operator=(const INavigationProcessor&) = delete;
  INavigationProcessor(INavigationProcessor&&) = default;
  INavigationProcessor& operator=(INavigationProcessor&&) = default;

  virtual ~INavigationProcessor() = default;

  virtual std::optional<::protocols::navigation::Navigation> process(std::span<const Payload> payloads)
      = 0;
};

class NavigationProcessor : public INavigationProcessor {
 public:
  explicit NavigationProcessor();

  std::optional<::protocols::navigation::Navigation>
  process(std::span<const Payload> payloads) override;

 private:
};

} // namespace navigation

#endif // NAVIGATION_PROCESSING_DETECTION_PROCESSOR_H
