#ifndef GOAL_THINKX_H
#define GOAL_THINKX_H
#pragma warning (disable:4786)
#include "goals\Goal_Think.h"
#include "Raven_Bot_X.h"

class Goal_Think_X : public Goal_Think
{
public:

  Goal_Think_X(Raven_Bot_X* pBot);
  ~Goal_Think_X();
  int Process();
  void AddGoal_MoveToPosition(Vector2D pos);
  void AddGoal_GetItem(unsigned int ItemType);

  void Arbitrate();
};

#endif