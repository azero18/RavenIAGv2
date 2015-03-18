#ifndef GOAL_EXPLOREZ_H
#define GOAL_EXPLOREZ_H
#pragma warning (disable:4786)

#include "Goal_Composite_Z.h"
#include "goals/Raven_Goal_Types.h"


class Raven_Bot_Z;


class Goal_Explore_Z : public Goal_Composite_Z<Raven_Bot_Z>
{
private:
  
  Vector2D  m_CurrentDestination;

  //set to true when the destination for the exploration has been established
  bool      m_bDestinationIsSet;

public:

  Goal_Explore_Z(Raven_Bot_Z* pOwner):Goal_Composite_Z<Raven_Bot_Z>(pOwner,
                                                            goal_explore_Z),
                                  m_bDestinationIsSet(false)
  {}


  void Activate();

  int Process();

  void Terminate(){}

  bool HandleMessage(const Telegram& msg);
};





#endif
