#include "ExploreGoal_Evaluator_Z.h"
#include "navigation/Raven_PathPlanner.h"
#include "Raven_ObjectEnumerations.h"
#include "lua/Raven_Scriptor.h"
#include "misc/Stream_Utility_Functions.h"
#include "RavenFeature_Z.h"

#include "Goal_Think_Z.h"
#include "goals/Raven_Goal_Types.h"




//---------------- CalculateDesirability -------------------------------------
//-----------------------------------------------------------------------------
double ExploreGoal_Evaluator_Z::CalculateDesirability(Raven_Bot_Z* pBot)
{
  double Desirability = 0.05;

  Desirability *= m_dCharacterBias;

  return Desirability;
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void ExploreGoal_Evaluator_Z::SetGoal(Raven_Bot_Z* pBot)
{
  pBot->GetBrain_Z()->AddGoal_Explore();
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void ExploreGoal_Evaluator_Z::RenderInfo(Vector2D Position, Raven_Bot_Z* pBot)
{
  gdi->TextAtPos(Position, "EX: " + ttos(CalculateDesirability(pBot), 2));
}