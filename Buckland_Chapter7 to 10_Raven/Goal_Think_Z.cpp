#include "Goal_Think_Z.h"
#include "Goal_MoveToPosition_Z.h"
#include "Goal_GetItem_Z.h"

Goal_Think_Z::Goal_Think_Z(Raven_Bot_Z* pBot):Goal_Think(pBot, goal_think_Z)
{
  const double LowRangeOfBias = 0.5;
  const double HighRangeOfBias = 1.5;

  double HealthBias = RandInRange(LowRangeOfBias, HighRangeOfBias);
  double ShotgunBias = RandInRange(LowRangeOfBias, HighRangeOfBias);
  double RocketLauncherBias = RandInRange(LowRangeOfBias, HighRangeOfBias);
  double RailgunBias = RandInRange(LowRangeOfBias, HighRangeOfBias);
  double ExploreBias = RandInRange(LowRangeOfBias, HighRangeOfBias);
  double AttackBias = RandInRange(LowRangeOfBias, HighRangeOfBias);


  m_Evaluators.push_back(new GetHealthGoal_Evaluator(HealthBias));
  m_Evaluators.push_back(new ExploreGoal_Evaluator(ExploreBias));
  m_Evaluators.push_back(new AttackTargetGoal_Evaluator(AttackBias));
  m_Evaluators.push_back(new GetWeaponGoal_Evaluator(ShotgunBias,
                                                     type_shotgun));
  m_Evaluators.push_back(new GetWeaponGoal_Evaluator(RailgunBias,
                                                     type_rail_gun));
  m_Evaluators.push_back(new GetWeaponGoal_Evaluator(RocketLauncherBias,
                                                     type_rocket_launcher));

  ResetItemEvalMod();
}

Goal_Think_Z::~Goal_Think_Z()
{

}

int Goal_Think_Z::Process()
{
  ActivateIfInactive();
  
  Arbitrate();

  int SubgoalStatus = ProcessSubgoals();

  if (SubgoalStatus == completed || SubgoalStatus == failed)
  {
    if (!m_pOwner->isPossessed())
    {
      m_iStatus = inactive;
    }
  }

  return m_iStatus;
}

void Goal_Think_Z::Arbitrate()
{
  double best = 0;
  Goal_Evaluator* MostDesirable = 0;

  //iterate through all the evaluators to see which produces the highest score
  GoalEvaluators::iterator curDes = m_Evaluators.begin();
  for (curDes; curDes != m_Evaluators.end(); ++curDes)
  {
    double desirabilty = (*curDes)->CalculateDesirability(m_pOwner);
	//if ((*curDes)->getTypeNum() == 3){desirabilty *= GetitemEvalMod();}
    if (desirabilty >= best)
    {
      best = desirabilty;
      MostDesirable = *curDes;
    }
  }

  assert(MostDesirable && "<Goal_Think::Arbitrate>: no evaluator selected");
  
  //if (MostDesirable->getTypeNum() == 3){ResetItemEvalMod();}
  MostDesirable->SetGoal(m_pOwner);
}

void Goal_Think_Z::AddGoal_MoveToPosition(Vector2D pos)
{//NEW: Revisar essa bagaca se precisar
  AddSubgoal( new Goal_MoveToPosition_Z(m_pOwner, pos));
}

void Goal_Think_Z::AddGoal_GetItem(unsigned int ItemType)
{
  if (notPresent(ItemTypeToGoalType_Z(ItemType)))
  {
    RemoveAllSubgoals();
    AddSubgoal( new Goal_GetItem_Z(m_pOwner, ItemType));
  }
}

