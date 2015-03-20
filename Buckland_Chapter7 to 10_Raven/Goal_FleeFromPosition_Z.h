#ifndef GOAL_FLEE_FROM_POSITIONZ_H
#define GOAL_FLEE_FROM_POSITIONZ_H
#pragma warning (disable:4786)

#include "Goals/Goal.h"
#include "2d/Vector2D.h"
#include "goals/Raven_Goal_Types.h"
#include "Raven_Bot.h"


class Goal_FleeFromPosition_Z : public Goal<Raven_Bot>
{
private:

  //the position the bot is moving to
  Vector2D  m_vPosition;

  //the approximate time the bot should take to travel the target location
  double     m_dTimeToReachPos;
  
  //this records the time this goal was activated
  double     m_dStartTime;

  //returns true if a bot gets stuck
  bool      isStuck()const;

public:

  Goal_FleeFromPosition_Z(Raven_Bot* pBot, Vector2D target);

  //the usual suspects
  void Activate();
  int  Process();
  void Terminate();

  void Render();
};




#endif

