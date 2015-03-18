#ifndef GOAL_ENUMERATIONSZ_H
#define GOAL_ENUMERATIONSZ_H

#include <string>
#include "misc/TypeToString.h"

enum
{
  goal_think_Z,
  goal_explore_Z,
  goal_arrive_at_position_Z,
  goal_seek_to_position_Z,
  goal_follow_path_Z,
  goal_traverse_edge_Z,
  goal_move_to_position_Z,
  goal_get_health_Z,
  goal_get_shotgun_Z,
  goal_get_rocket_launcher_Z,
  goal_get_railgun_Z,
  goal_wander_Z,
  goal_negotiate_door_Z,
  goal_attack_target_Z,
  goal_hunt_target_Z,
  goal_strafe_Z,
  goal_adjust_range_Z,
  goal_say_phrase_Z
  
};

class GoalTypeToString : public TypeToString
{

  GoalTypeToString(){}

public:

  static GoalTypeToString* Instance();
  
  std::string Convert(int gt);
};

#endif
