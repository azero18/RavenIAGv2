#include "Goal_NegotiateDoor_Z.h"
#include "Raven_Bot_Z.h"
#include "Raven_Game.h"
#include "navigation/Raven_PathPlanner.h"


#include "Goal_MoveToPosition_Z.h"
#include "Goal_TraverseEdge_Z.h"


#include "debug/DebugConsole.h"



//---------------------------- ctor -------------------------------------------
//-----------------------------------------------------------------------------
Goal_NegotiateDoor_Z::
Goal_NegotiateDoor_Z(Raven_Bot_Z*   pBot,
                   PathEdge     edge,
                   bool         LastEdge):Goal_Composite_Z<Raven_Bot_Z>(pBot, goal_negotiate_door_Z),
                                        m_PathEdge(edge),
                                        m_bLastEdgeInPath(LastEdge)

{
}

//---------------------------- Activate ---------------------------------------
//-----------------------------------------------------------------------------
void Goal_NegotiateDoor_Z::Activate()
{
  m_iStatus = active;
  
  //if this goal is reactivated then there may be some existing subgoals that
  //must be removed
  RemoveAllSubgoals();
  
  //get the position of the closest navigable switch
  Vector2D posSw = m_pOwner->GetWorld()->GetPosOfClosestSwitch(m_pOwner->Pos(),
                                                          m_PathEdge.DoorID());

  //because goals are *pushed* onto the front of the subgoal list they must
  //be added in reverse order.
  
  //first the goal to traverse the edge that passes through the door  
  AddSubgoal(new Goal_TraverseEdge_Z(m_pOwner, m_PathEdge, m_bLastEdgeInPath));

  //next, the goal that will move the bot to the beginning of the edge that
  //passes through the door
  AddSubgoal(new Goal_MoveToPosition_Z(m_pOwner, m_PathEdge.Source()));
  
  //finally, the Goal that will direct the bot to the location of the switch
  AddSubgoal(new Goal_MoveToPosition_Z(m_pOwner, posSw));
}


//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_NegotiateDoor_Z::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();

  //process the subgoals
  m_iStatus = ProcessSubgoals();

  return m_iStatus;
}




