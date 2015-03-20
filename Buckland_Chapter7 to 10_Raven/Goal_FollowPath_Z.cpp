#include "Goal_FollowPath_Z.h"
#include "Raven_Bot.h"
#include "Raven_Game.h"

#include "Raven_SensoryMemory.h"

#include "goals/Goal_TraverseEdge.h"
#include "goals/Goal_NegotiateDoor.h"
#include "goals/Goal_AttackTarget.h"
#include "misc/cgdi.h"


#include "debug/DebugConsole.h"

//------------------------------ ctor -----------------------------------------
//-----------------------------------------------------------------------------
Goal_FollowPath_Z::
Goal_FollowPath_Z(Raven_Bot*          pBot,
                std::list<PathEdge> path):Goal_Composite<Raven_Bot>(pBot, goal_follow_path),
                                                  m_Path(path)
{
  //get a reference to the final edge
  PathEdge finaledge = m_Path.back();
  goalPos = finaledge.Destination();
  std::list<Raven_Bot*> SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();
  lastISize = SensedBots.size();
}


//------------------------------ Activate -------------------------------------
//-----------------------------------------------------------------------------
void Goal_FollowPath_Z::Activate()
{
  m_iStatus = active;
  
  //get a reference to the next edge
  PathEdge edge = m_Path.front();

  //remove the edge from the path
  m_Path.pop_front(); 

  //some edges specify that the bot should use a specific behavior when
  //following them. This switch statement queries the edge behavior flag and
  //adds the appropriate goals/s to the subgoal list.
 // double ClosestDistSoFar = MaxDouble;
 // std::list<Raven_Bot*> SensedBots;
 // SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();
 // int actualISize = SensedBots.size(); 

 // std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
 // double distA = Vec2DDistanceSq(m_pOwner->Pos(), goalPos);
 // Raven_Bot* DangerBot = nullptr;
 // double distE = MaxDouble;
 // for (curBot; curBot != SensedBots.end(); ++curBot)
 // {
 //   //make sure the bot is alive and that it is not the owner
	//bool isVisible = m_pOwner->GetSensoryMem()->isOpponentWithinFOV((*curBot));
	//
	//if ((*curBot)->isAlive() && (*curBot != m_pOwner) && (isVisible))
 //   {	  
	//  if (actualISize > lastISize)
	//  {
	//	double distC = Vec2DDistance(m_pOwner->Pos(),(*curBot)->Pos());
	//	double distD = m_pOwner->BRadius()*12;//danger distance
	//	debug_con << "DANGER "<< distC << " "<< distD << " \n";
	//	if (distC < distD)
	//	{
	//		if (distC < distE)
	//		{debug_con << "DANGER pt 2 \n";
	//		  DangerBot = (*curBot);
	//		  distE = distC;
	//		}
	//	}
	//  }
	//  
 //     double distB = Vec2DDistanceSq((*curBot)->Pos(), goalPos);

 //     if (distB < ClosestDistSoFar)
 //     {
 //       ClosestDistSoFar = distB;        
 //     }
 //   }	
 // }

 // if (actualISize > lastISize)
 // {
	//  debug_con << "DANGER pt 3 \n";
	//  if (distE < MaxDouble)
	//  {
	//	  AddSubgoal(new Goal_AttackTarget(m_pOwner));
	//	  debug_con << "DANGER pt 4 \n";
	//  }
 // }else
 // {
 // if (distA < ClosestDistSoFar)
 // {
	  switch(edge.Behavior())
	  {
	  case NavGraphEdge::normal:
		{
		  AddSubgoal(new Goal_TraverseEdge(m_pOwner, edge, m_Path.empty()));
		}

		break;

	  case NavGraphEdge::goes_through_door:
		{

		  //also add a goal that is able to handle opening the door
		  AddSubgoal(new Goal_NegotiateDoor(m_pOwner, edge, m_Path.empty()));
		}

		break;

	  case NavGraphEdge::jump:
		{
		  //add subgoal to jump along the edge
		}

		break;

	  case NavGraphEdge::grapple:
		{
		  //add subgoal to grapple along the edge
		}

		break;

	  default:

		throw std::runtime_error("<Goal_FollowPath::Activate>: Unrecognized edge type");
	  }
  //}else
  //{
	 // //m_iStatus = losing_will;
	 // //debug_con << "BOT HAS LOST WILL ";
  //}
  //}
}


//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Goal_FollowPath_Z::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();

  m_iStatus = ProcessSubgoals();

  //if there are no subgoals present check to see if the path still has edges.
  //remaining. If it does then call activate to grab the next edge.
  if (m_iStatus == completed && !m_Path.empty())
  {
    Activate(); 
  }

  return m_iStatus;
}
 
//---------------------------- Render -----------------------------------------
//-----------------------------------------------------------------------------
void Goal_FollowPath_Z::Render()
{ 
  //render all the path waypoints remaining on the path list
  std::list<PathEdge>::iterator it;
  for (it = m_Path.begin(); it != m_Path.end(); ++it)
  {  
    gdi->BlackPen();
    gdi->LineWithArrow(it->Source(), it->Destination(), 5);
    
    gdi->RedBrush();
    gdi->BlackPen();
    gdi->Circle(it->Destination(), 3);
  }
  gdi->PurplePen();
  //gdi->Circle(m_pOwner->Pos(),m_pOwner->BRadius()*15);

  //forward the request to the subgoals
  Goal_Composite<Raven_Bot>::Render();
}
  




