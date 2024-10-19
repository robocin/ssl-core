#include "elapsed_timer.h"

#include "robocin/version/version.h"

#if defined(__robocin_lib_std_concurrency) and __robocin_lib_std_concurrency >= 202405L

#include "robocin/detection_util/clock.h"

namespace robocin::detection_util {

/*Constructs an invalid ElapsedTimer. A timer becomes valid once it has been started.*/
ElapsedTimer::ElapsedTimer(bool started) : started_{started}, valid_ {false}, start_{Clock::now()} {}

void ElapsedTimer::stop() { started_ = false; }

/*starting a timer makes it valid again.*/
void ElapsedTimer::start() { started_ = true, valid_ = true, start_ = Clock::now(); }

/*Restarts the timer and returns the number of nanoseconds elapsed since the previous start.
Calling this function on a ElapsedTimer that is invalid results in undefined behavior.*/
Duration ElapsedTimer::restart() {
  if(valid_){
    started_ = true;
    valid_ = true;
    Duration result = this->elapsed();
    return start_ = Clock::now(), result;
  }
}

bool ElapsedTimer::isStarted() const { return started_; }

/* Returns false if the timer has never been started 
or invalidated by a call to invalidate().*/
bool ElapsedTimer::isValid() const noexcept { return valid_; }

/*Marks this object as invalid. Calculations of timer elapsed since
 the data invalidation are undefined and will likely produce bizarre results.*/
void ElapsedTimer::invalidate() noexcept { valid_ = false; }

/*returns time in nanoseconds.
Calling this function on a ElapsedTimer that is invalid results in undefined behavior.*/
Duration ElapsedTimer::elapsed() const {
  if(valid_){
    return started_ ? Frames(/*frames=*/0) : Clock::now() - start_;
  }
}

} // namespace robocin::detection_util

#endif
