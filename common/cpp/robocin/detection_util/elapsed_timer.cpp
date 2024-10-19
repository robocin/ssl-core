#include "elapsed_timer.h"

#include "robocin/version/version.h"

#if defined(__robocin_lib_std_concurrency) and __robocin_lib_std_concurrency >= 202405L

#include "robocin/detection_util/clock.h"

namespace robocin::detection_util {

ElapsedTimer::ElapsedTimer(bool started) : started_{started}, valid_ = true, start_{Clock::now()} {}

void ElapsedTimer::stop() { started_ = false; }

void ElapsedTimer::start() { started_ = true, valid_ = true, start_ = Clock::now(); }

Duration ElapsedTimer::restart() {
  started_ = true;
  valid_ = true;
  Duration result = this->elapsed();
  return start_ = Clock::now(), result;
}

bool ElapsedTimer::isStarted() const { return started_; }

bool isValid() const noexcept { return valid_; }

void invalidate() noexcept { valid_ = false; }

Duration ElapsedTimer::elapsed() const {
  return started_ ? Frames(/*frames=*/0) : Clock::now() - start_;
}

} // namespace robocin::detection_util

#endif
