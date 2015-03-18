#ifndef RAVEN_HEALTHZ_EVALUATOR
#define RAVEN_HEALTHZ_EVALUATOR
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   GetHealthGoal_Evaluator.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to calculate how desirable the goal of fetching a health item
//          is
//-----------------------------------------------------------------------------

#include "Goal_Evaluator_Z.h"
#include "Raven_Bot_Z.h"

class GetHealthGoal_Evaluator_Z : public Goal_Evaluator_Z
{
public:

  GetHealthGoal_Evaluator_Z(double bias):Goal_Evaluator_Z(bias){}
  
  double CalculateDesirability(Raven_Bot_Z* pBot);

  void  SetGoal(Raven_Bot_Z* pEnt);

  void RenderInfo(Vector2D Position, Raven_Bot_Z* pBot);
};

#endif
    
