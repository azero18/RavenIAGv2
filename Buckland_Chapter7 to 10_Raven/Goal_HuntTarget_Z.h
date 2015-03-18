#ifndef GOAL_FIND_TARGETZ_H
#define GOAL_FIND_TARGETZ_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_HuntTarget.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Causes a bot to search for its current target. Exits when target
//          is in view
//-----------------------------------------------------------------------------
#include "Goal_Composite_Z.h"
#include "goals/Raven_Goal_Types.h"
#include "Raven_Bot_Z.h"


class Goal_HuntTarget_Z : public Goal_Composite_Z<Raven_Bot_Z>
{
private:

  //this value is set to true if the last visible position of the target
  //bot has been searched without success
  bool  m_bLVPTried;

public:

  Goal_HuntTarget_Z(Raven_Bot_Z* pBot):Goal_Composite_Z<Raven_Bot_Z>(pBot, goal_hunt_target_Z),
                                   m_bLVPTried(false)
  {}

   //the usual suspects
  void Activate();
  int  Process();
  void Terminate(){}

  void Render();


};





#endif
