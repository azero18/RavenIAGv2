#ifndef GOAL_MOVE_POSZ_H
#define GOAL_MOVE_POSZ_H
#pragma warning (disable:4786)

#include "Goal_Composite_Z.h"
#include "2D/Vector2D.h"
#include "Raven_Bot_Z.h"
#include "Raven_Goal_Types_Z.h"



class Goal_MoveToPosition_Z : public Goal_Composite_Z<Raven_Bot_Z>
{
private:

  //the position the bot wants to reach
  Vector2D m_vDestination;

public:

  Goal_MoveToPosition_Z(Raven_Bot_Z* pBot,
                      Vector2D   pos):
  
            Goal_Composite_Z<Raven_Bot_Z>(pBot,
                                      goal_move_to_position_Z),
            m_vDestination(pos)
  {}

 //the usual suspects
  void Activate();
  int  Process();
  void Terminate(){}

  //this goal is able to accept messages
  bool HandleMessage(const Telegram& msg);

  void Render();
};





#endif
