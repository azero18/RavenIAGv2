#include "Goal_Think_X.h"
#include "goals/Goal_MoveToPosition.h"
#include "goals/Goal_GetItem.h"

Goal_Think_X::Goal_Think_X(Raven_Bot_X* pBot):Goal_Think(pBot, goal_think)
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

}

Goal_Think_X::~Goal_Think_X()
{

}

int Goal_Think_X::Process()
{
  ActivateIfInactive();
  
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

void Goal_Think_X::Arbitrate()
{
  double best = 0;
  Goal_Evaluator* MostDesirable = 0;

  //iterate through all the evaluators to see which produces the highest score
  GoalEvaluators::iterator curDes = m_Evaluators.begin();
  for (curDes; curDes != m_Evaluators.end(); ++curDes)
  {
    double desirabilty = (*curDes)->CalculateDesirability(m_pOwner);
    if (desirabilty >= best)
    {
      best = desirabilty;
      MostDesirable = *curDes;
    }
  }

  assert(MostDesirable && "<Goal_Think::Arbitrate>: no evaluator selected");
  
  MostDesirable->SetGoal(m_pOwner);
}

void Goal_Think_X::AddGoal_MoveToPosition(Vector2D pos)
{
  AddSubgoal( new Goal_MoveToPosition(m_pOwner, pos));
}

void Goal_Think_X::AddGoal_GetItem(unsigned int ItemType)
{
  if (notPresent(ItemTypeToGoalType(ItemType)))
  {
    RemoveAllSubgoals();
    AddSubgoal( new Goal_GetItem(m_pOwner, ItemType));
  }
}