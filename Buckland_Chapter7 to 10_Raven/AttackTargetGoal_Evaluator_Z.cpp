#include "AttackTargetGoal_Evaluator_Z.h"
#include "Goal_Think_Z.h"
#include "goals/Raven_Goal_Types.h"
#include "Raven_WeaponSystem.h"
#include "Raven_ObjectEnumerations.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "RavenFeature_Z.h"


#include "debug/DebugConsole.h"

//------------------ CalculateDesirability ------------------------------------
//
//  returns a value between 0 and 1 that indicates the Rating of a bot (the
//  higher the score, the stronger the bot).
//-----------------------------------------------------------------------------
double AttackTargetGoal_Evaluator_Z::CalculateDesirability(Raven_Bot_Z* pBot)
{
  double Desirability = 0.0;

  //only do the calculation if there is a target present
  if (pBot->GetTargetSys()->isTargetPresent()) 
  {
     const double Tweaker = 1.0;

     Desirability = Tweaker *
                    Raven_Feature_Z::Health(pBot) * 
                    Raven_Feature_Z::TotalWeaponStrength(pBot);

     //bias the value according to the personality of the bot
     Desirability *= m_dCharacterBias;
  }
    
  return Desirability;
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void AttackTargetGoal_Evaluator_Z::SetGoal(Raven_Bot_Z* pBot)
{
  pBot->GetBrain_Z()->AddGoal_AttackTarget(); 
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void AttackTargetGoal_Evaluator_Z::RenderInfo(Vector2D Position, Raven_Bot_Z* pBot)
{
  gdi->TextAtPos(Position, "AT: " + ttos(CalculateDesirability(pBot), 2));
  return;
    
  std::string s = ttos(Raven_Feature_Z::Health(pBot)) + ", " + ttos(Raven_Feature_Z::TotalWeaponStrength(pBot));
  gdi->TextAtPos(Position+Vector2D(0,12), s);
}