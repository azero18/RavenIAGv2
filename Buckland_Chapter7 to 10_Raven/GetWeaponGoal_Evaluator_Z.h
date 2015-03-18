#ifndef RAVEN_WEAPONZ_EVALUATOR
#define RAVEN_WEAPONZ_EVALUATOR
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   GetWeaponGoal_Evaluator.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:  class to calculate how desirable the goal of fetching a weapon item
//         is 
//-----------------------------------------------------------------------------

#include "Goal_Evaluator_Z.h"
#include "Raven_Bot_Z.h"


class GetWeaponGoal_Evaluator_Z : public Goal_Evaluator_Z
{ 
  int   m_iWeaponType;

public:

  GetWeaponGoal_Evaluator_Z(double bias,
                          int   WeaponType):Goal_Evaluator_Z(bias),
                                            m_iWeaponType(WeaponType)
  {}
  
  double CalculateDesirability(Raven_Bot_Z* pBot);

  void  SetGoal(Raven_Bot_Z* pEnt);

  void  RenderInfo(Vector2D Position, Raven_Bot_Z* pBot);
};

#endif