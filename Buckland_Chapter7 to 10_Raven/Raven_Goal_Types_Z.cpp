#include "Raven_Goal_Types_Z.h"


GoalTypeToString* GoalTypeToString::Instance()
{
  static GoalTypeToString instance;
  return &instance;
}

std::string GoalTypeToString::Convert(int gt)
{
  switch(gt)
  {
  case goal_explore_Z:

    return "explore";

  case goal_think_Z:

    return "think";

  case goal_arrive_at_position_Z:

    return "arrive_at_position";

  case goal_seek_to_position_Z:

    return "seek_to_position";

  case goal_follow_path_Z:

    return "follow_path";

  case goal_traverse_edge_Z:

    return "traverse_edge";

  case goal_move_to_position_Z:

    return "move_to_position";

  case goal_get_health_Z:

    return "get_health";

  case goal_get_shotgun_Z:

    return "get_shotgun";

  case goal_get_railgun_Z:

    return "get_railgun";

  case goal_get_rocket_launcher_Z:

    return "get_rocket_launcher";

  case goal_wander_Z:

    return "wander";

  case goal_negotiate_door_Z:

    return "negotiate_door";

  case goal_attack_target_Z:

    return "attack_target";

  case goal_hunt_target_Z:

    return "hunt_target";

  case goal_strafe_Z:

    return "strafe";

  case goal_adjust_range_Z:

    return "adjust_range";

  case goal_say_phrase_Z:

    return "say_phrase";

  default:

    return "UNKNOWN GOAL TYPE!";

  }//end switch
}