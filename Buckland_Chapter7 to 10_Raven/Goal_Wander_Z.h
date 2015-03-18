#ifndef GOAL_WANDERZ_H
#define GOAL_WANDERZ_H
#pragma warning (disable:4786)

#include "Goal_Z.h"
#include "goals/Raven_Goal_Types.h"
#include "Raven_Bot_Z.h"


class Goal_Wander_Z : public Goal_Z<Raven_Bot_Z>
{
private:

public:

  Goal_Wander_Z(Raven_Bot_Z* pBot):Goal_Z<Raven_Bot_Z>(pBot,goal_wander_Z)
  {}

  void Activate();

  int  Process();

  void Terminate();
};





#endif
