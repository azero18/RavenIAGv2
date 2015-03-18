#ifndef GOAL_ATTACKTARGETZ_H
#define GOAL_ATTACKTARGETZ_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_AttackTarget.h
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:   
//
//-----------------------------------------------------------------------------
#include "Goal_Composite_Z.h"
#include "Raven_Goal_Types_Z.h"
#include "Raven_Bot_Z.h"





class Goal_AttackTarget_Z : public Goal_Composite_Z<Raven_Bot_Z>
{
public:

  Goal_AttackTarget_Z(Raven_Bot_Z* pOwner):Goal_Composite_Z<Raven_Bot_Z>(pOwner, goal_attack_target_Z)
  {}

  void Activate();

  int  Process();

  void Terminate(){m_iStatus = completed;}

};






#endif
