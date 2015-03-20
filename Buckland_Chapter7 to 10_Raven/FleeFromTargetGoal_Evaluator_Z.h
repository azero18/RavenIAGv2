#ifndef RAVEN_COWARDZ_EVALUATOR
#define RAVEN_COWARDZ_EVALUATOR
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

#include "goals/Goal_Evaluator.h"
#include "Raven_Bot.h"

class FleeFromTargetGoal_Evaluator_Z : public Goal_Evaluator
{
public:

  FleeFromTargetGoal_Evaluator_Z(double bias):Goal_Evaluator(bias){}
  
  double CalculateDesirability(Raven_Bot* pBot);

  void  SetGoal(Raven_Bot* pEnt);

  void RenderInfo(Vector2D Position, Raven_Bot* pBot);

  int  getTypeNum(){return 5;};
};

#endif
    
