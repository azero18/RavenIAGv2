#include "Goal_Think_Z.h"
#include <list>
#include "misc/Cgdi.h"
#include "Raven_ObjectEnumerations.h"
#include "misc/utils.h"
#include "lua\Raven_Scriptor.h"

#include "Goal_MoveToPosition_Z.h"
#include "Goal_Explore_Z.h"
#include "Goal_GetItem_Z.h"
#include "Goal_Wander_Z.h"
#include "Raven_Goal_Types_Z.h"
#include "Goal_AttackTarget_Z.h"


#include "GetWeaponGoal_Evaluator_Z.h"
#include "GetHealthGoal_Evaluator_Z.h"
#include "ExploreGoal_Evaluator_Z.h"
#include "AttackTargetGoal_Evaluator_Z.h"


Goal_Think_Z::Goal_Think_Z(Raven_Bot_Z* pBot):Goal_Composite_Z<Raven_Bot_Z>(pBot, goal_think_Z)
{
  
  //these biases could be loaded in from a script on a per bot basis
  //but for now we'll just give them some random values
  const double LowRangeOfBias = 0.5;
  const double HighRangeOfBias = 1.5;

  double HealthBias = RandInRange(LowRangeOfBias, HighRangeOfBias);
  double ShotgunBias = RandInRange(LowRangeOfBias, HighRangeOfBias);
  double RocketLauncherBias = RandInRange(LowRangeOfBias, HighRangeOfBias);
  double RailgunBias = RandInRange(LowRangeOfBias, HighRangeOfBias);
  double ExploreBias = RandInRange(LowRangeOfBias, HighRangeOfBias);
  double AttackBias = RandInRange(LowRangeOfBias, HighRangeOfBias);

  //create the evaluator objects
  m_Evaluators.push_back(new GetHealthGoal_Evaluator_Z(HealthBias));
  m_Evaluators.push_back(new ExploreGoal_Evaluator_Z(ExploreBias));
  m_Evaluators.push_back(new AttackTargetGoal_Evaluator_Z(AttackBias));
  m_Evaluators.push_back(new GetWeaponGoal_Evaluator_Z(ShotgunBias,
                                                     type_shotgun));
  m_Evaluators.push_back(new GetWeaponGoal_Evaluator_Z(RailgunBias,
                                                     type_rail_gun));
  m_Evaluators.push_back(new GetWeaponGoal_Evaluator_Z(RocketLauncherBias,
                                                     type_rocket_launcher));
}

//----------------------------- dtor ------------------------------------------
//-----------------------------------------------------------------------------
Goal_Think_Z::~Goal_Think_Z()
{
  GoalEvaluators::iterator curDes = m_Evaluators.begin();
  for (curDes; curDes != m_Evaluators.end(); ++curDes)
  {
    delete *curDes;
  }
}

//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_Think_Z::Activate()
{
  if (!m_pOwner->isPossessed())
  {
    Arbitrate();
  }

  m_iStatus = active;
}

//------------------------------ Process --------------------------------------
//
//  processes the subgoals
//-----------------------------------------------------------------------------
int Goal_Think_Z::Process()
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

//----------------------------- Update ----------------------------------------
// 
//  this method iterates through each goal option to determine which one has
//  the highest desirability.
//-----------------------------------------------------------------------------
void Goal_Think_Z::Arbitrate()
{
  double best = 0;
  Goal_Evaluator_Z* MostDesirable = 0;

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


//---------------------------- notPresent --------------------------------------
//
//  returns true if the goal type passed as a parameter is the same as this
//  goal or any of its subgoals
//-----------------------------------------------------------------------------
bool Goal_Think_Z::notPresent(unsigned int GoalType)const
{
  if (!m_SubGoals.empty())
  {
    return m_SubGoals.front()->GetType() != GoalType;
  }

  return true;
}

void Goal_Think_Z::AddGoal_MoveToPosition(Vector2D pos)
{
  AddSubgoal( new Goal_MoveToPosition_Z(m_pOwner, pos));
}

void Goal_Think_Z::AddGoal_Explore()
{
  if (notPresent(goal_explore_Z))
  {
    RemoveAllSubgoals();
    AddSubgoal( new Goal_Explore_Z(m_pOwner));
  }
}

void Goal_Think_Z::AddGoal_GetItem(unsigned int ItemType)
{
  if (notPresent(ItemTypeToGoalType(ItemType)))
  {
    RemoveAllSubgoals();
    AddSubgoal( new Goal_GetItem_Z(m_pOwner, ItemType));
  }
}

void Goal_Think_Z::AddGoal_AttackTarget()
{
  if (notPresent(goal_attack_target_Z))
  {
    RemoveAllSubgoals();
    AddSubgoal( new Goal_AttackTarget_Z(m_pOwner));
  }
}

//-------------------------- Queue Goals --------------------------------------
//-----------------------------------------------------------------------------
void Goal_Think_Z::QueueGoal_MoveToPosition(Vector2D pos)
{
   m_SubGoals.push_back(new Goal_MoveToPosition_Z(m_pOwner, pos));
}



//----------------------- RenderEvaluations -----------------------------------
//-----------------------------------------------------------------------------
void Goal_Think_Z::RenderEvaluations(int left, int top)const
{
  gdi->TextColor(Cgdi::black);
  
  std::vector<Goal_Evaluator_Z*>::const_iterator curDes = m_Evaluators.begin();
  for (curDes; curDes != m_Evaluators.end(); ++curDes)
  {
    (*curDes)->RenderInfo(Vector2D(left, top), m_pOwner);

    left += 75;
  }
}

void Goal_Think_Z::Render()
{
  std::list<Goal_Z<Raven_Bot_Z>*>::iterator curG;
  for (curG=m_SubGoals.begin(); curG != m_SubGoals.end(); ++curG)
  {
    (*curG)->Render();
  }
}


   
