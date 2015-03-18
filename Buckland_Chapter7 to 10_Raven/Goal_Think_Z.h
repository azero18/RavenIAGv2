#ifndef GOAL_THINKZ_H
#define GOAL_THINKZ_H
#pragma warning (disable:4786)

#include <vector>
#include <string>
#include "2d/Vector2D.h"
#include "Goal_Composite_Z.h"
#include "Raven_Bot_Z.h"
#include "Goal_Evaluator_Z.h"


class Goal_Think_Z : public Goal_Composite_Z<Raven_Bot_Z>
{
private:
  
  typedef std::vector<Goal_Evaluator_Z*>   GoalEvaluators;

private:
  
  GoalEvaluators  m_Evaluators;

public:

  Goal_Think_Z(Raven_Bot_Z* pBot);
  ~Goal_Think_Z();

  //this method iterates through each goal evaluator and selects the one
  //that has the highest score as the current goal
  void Arbitrate();

  //returns true if the given goal is not at the front of the subgoal list
  bool notPresent(unsigned int GoalType)const;

  //the usual suspects
  int  Process();
  void Activate();
  void Terminate(){}
  
  //top level goal types
  void AddGoal_MoveToPosition(Vector2D pos);
  void AddGoal_GetItem(unsigned int ItemType);
  void AddGoal_Explore();
  void AddGoal_AttackTarget();

  //this adds the MoveToPosition goal to the *back* of the subgoal list.
  void QueueGoal_MoveToPosition(Vector2D pos);

  //this renders the evaluations (goal scores) at the specified location
  void  RenderEvaluations(int left, int top)const;
  void  Render();


};


#endif