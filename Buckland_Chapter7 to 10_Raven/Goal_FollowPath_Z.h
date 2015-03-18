#ifndef GOAL_FOLLOWPATHZ_H
#define GOAL_FOLLOWPATHZ_H
#pragma warning (disable:4786)

#include "Goal_Composite_Z.h"
#include "goals/Raven_Goal_Types.h"
#include "Raven_Bot_Z.h"
#include "navigation/Raven_PathPlanner.h"
#include "navigation/PathEdge.h"



class Goal_FollowPath_Z : public Goal_Composite_Z<Raven_Bot_Z>
{
private:

  //a local copy of the path returned by the path planner
  std::list<PathEdge>  m_Path;

public:

  Goal_FollowPath_Z(Raven_Bot_Z* pBot, std::list<PathEdge> path);

  //the usual suspects
  void Activate();
  int Process();
  void Render();
  void Terminate(){}
};

#endif

