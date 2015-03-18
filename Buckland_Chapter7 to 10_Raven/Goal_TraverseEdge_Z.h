#ifndef GOAL_TRAVERSE_EDGEZ_H
#define GOAL_TRAVERSE_EDGEZ_H
#pragma warning (disable:4786)

#include "Goal_Z.h"
#include "2d/Vector2D.h"
#include "navigation/Raven_PathPlanner.h"
#include "navigation/PathEdge.h"
#include "Raven_Bot_Z.h"


class Goal_TraverseEdge_Z : public Goal_Z<Raven_Bot_Z>
{
private:

  //the edge the bot will follow
  PathEdge  m_Edge;

  //true if m_Edge is the last in the path.
  bool      m_bLastEdgeInPath;

  //the estimated time the bot should take to traverse the edge
  double     m_dTimeExpected;
  
  //this records the time this goal was activated
  double     m_dStartTime;

  //returns true if the bot gets stuck
  bool      isStuck()const;

public:

  Goal_TraverseEdge_Z(Raven_Bot_Z* pBot,
                    PathEdge   edge,
                    bool       LastEdge); 

  //the usual suspects
  void Activate();
  int  Process();
  void Terminate();
  void Render();
};




#endif

