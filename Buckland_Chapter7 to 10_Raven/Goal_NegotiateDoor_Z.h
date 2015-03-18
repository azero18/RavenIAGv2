#ifndef GOAL_NEGOTIATE_DOORZ_H
#define GOAL_NEGOTIATE_DOORZ_H
#pragma warning (disable:4786)

#include "Goal_Composite_Z.h"
#include "Raven_Goal_Types_Z.h"
#include "Raven_Bot_Z.h"
#include "navigation/PathEdge.h"


class Goal_NegotiateDoor_Z : public Goal_Composite_Z<Raven_Bot_Z>
{
private:

  PathEdge m_PathEdge;

  bool     m_bLastEdgeInPath;

public:

  Goal_NegotiateDoor_Z(Raven_Bot_Z* pBot, PathEdge edge, bool LastEdge);

 //the usual suspects
  void Activate();
  int  Process();
  void Terminate(){}
};



#endif
