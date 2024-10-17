#include "communication/processing/robot_command/robot_command_mapper.h"

#include <google/protobuf/util/time_util.h>
#include <protocols/navigation/navigation.pb.h>
#include <protocols/communication/robot_info.pb.h> 
#include <protocols/third_party/game_controller/referee.pb.h>
#include <robocin/memory/object_ptr.h>
#include <utility>

namespace communication {
namespace {

using ::google::protobuf::util::TimeUtil;
using ::robocin::object_ptr;

namespace rc {
    
using ::protocols::navigation::Navigation;
using ::protocols::communication::RobotInfo;
using ::protocols::communication::Command;

} // namespace rc

namespace tp {

using ::protocols::third_party::game_controller::Referee;

} // namespace tp

} // namespace

RobotCommandMapper::RobotCommandMapper(){}

rc::RobotInfo RobotCommandMapper::fromNavigationAndReferee(const rc::Navigation& navigation, const tp::Referee& referee) {
    rc::RobotInfo result;
    rc::Command* command = result.mutable_command();

    // *command->mutable_msg_type(); // TODO

    // *command->mutable_robot_id(); // TODO

    // *command->mutable_ref_command(); // TODO

    // *command->mutable_robot_velocity(); // TODO

    // *command->mutable_kick_command(); // TODO

    // *command->mutable_dribble_command(); // TODO

    // *command->mutable_robot_flag(); // TODO

    return result;
}

} // namespace communication
