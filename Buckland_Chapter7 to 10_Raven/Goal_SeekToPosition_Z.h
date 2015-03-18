#ifndef GOAL_SEEK_TO_POSITIONZ_H
#define GOAL_SEEK_TO_POSITIONZ_H
#pragma warning (disable:4786)

#include "Goal_Z.h"
#include "2d/Vector2D.h"
#include "Raven_Goal_Types_Z.h"
#include "Raven_Bot_Z.h"


class Goal_SeekToPosition_Z : public Goal_Z<Raven_Bot_Z>
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

  Goal_SeekToPosition_Z(Raven_Bot_Z* pBot, Vector2D target);
  

  //the usual suspects
  void Activate();
  int  Process();
  void Terminate();

  void Render();
};




#endif

