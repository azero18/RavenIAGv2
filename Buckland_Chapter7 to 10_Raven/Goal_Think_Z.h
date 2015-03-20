#ifndef GOAL_THINKZ_H
#define GOAL_THINKZ_H
#pragma warning (disable:4786)
#include "goals\Goal_Think.h"
#include "Raven_Bot_Z.h"

class Goal_Think_Z : public Goal_Think
{
public:

  Goal_Think_Z(Raven_Bot_Z* pBot);
  ~Goal_Think_Z();
  int Process();
  void AddGoal_MoveToPosition(Vector2D pos);
  void AddGoal_GetItem(unsigned int ItemType);

  void Arbitrate();
};

#endif