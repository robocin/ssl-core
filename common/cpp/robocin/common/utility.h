#ifndef ROBOCIN_COMMON_UTILITY_H
#define ROBOCIN_COMMON_UTILITY_H

#include <absl/time/time.h>
#include <google/protobuf/timestamp.pb.h>

namespace robocin {

::google::protobuf::Timestamp timestampNow();

::google::protobuf::Timestamp timestampFromNanos(int64_t nanos);

::google::protobuf::Timestamp timestampFromTime(const ::absl::Time& time);

::absl::Time timeFromTimestamp(const ::google::protobuf::Timestamp& timestamp);

} // namespace robocin

#endif // ROBOCIN_COMMON_UTILITY_H
