#ifndef GOAL_DODGE_SIDEZ_H
#define GOAL_DODGE_SIDEZ_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_DodgeSideToSide.h
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:   this goal makes the bot dodge from side to side
//
//-----------------------------------------------------------------------------
#include "Goal_Z.h"
#include "goals/Raven_Goal_Types.h"
#include "Raven_Bot_Z.h"





class Goal_DodgeSideToSide_Z : public Goal_Z<Raven_Bot_Z>
{
private:

  Vector2D    m_vStrafeTarget;

  bool        m_bClockwise;

  Vector2D  GetStrafeTarget()const;


public:

  Goal_DodgeSideToSide_Z(Raven_Bot_Z* pBot):Goal_Z<Raven_Bot_Z>(pBot, goal_strafe_Z),
                                        m_bClockwise(RandBool())
  {}


  void Activate();

  int  Process();

  void Render();

  void Terminate();
 
};






#endif
