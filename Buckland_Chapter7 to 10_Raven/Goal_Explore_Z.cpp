#include "Goal_Explore_Z.h"
#include "Raven_Bot_Z.h"
#include "navigation/Raven_PathPlanner.h"
#include "Raven_Game.h"
#include "Raven_Map.h"
#include "Messaging/Telegram.h"
#include "Raven_Messages.h"

#include "Goal_SeekToPosition_Z.h"
#include "Goal_FollowPath_Z.h"



//------------------------------ Activate -------------------------------------
//-----------------------------------------------------------------------------
void Goal_Explore_Z::Activate()
{
  m_iStatus = active;

  //if this goal is reactivated then there may be some existing subgoals that
  //must be removed
  RemoveAllSubgoals();

  if (!m_bDestinationIsSet)
  {
    //grab a random location
    m_CurrentDestination = m_pOwner->GetWorld()->GetMap()->GetRandomNodeLocation();

    m_bDestinationIsSet = true;
  }

  //and request a path to that position
  m_pOwner->GetPathPlanner()->RequestPathToPosition(m_CurrentDestination);

  //the bot may have to wait a few update cycles before a path is calculated
  //so for appearances sake it simple ARRIVES at the destination until a path
  //has been found
  AddSubgoal(new Goal_SeekToPosition_Z(m_pOwner, m_CurrentDestination));
}

//------------------------------ Process -------------------------------------
//-----------------------------------------------------------------------------
int Goal_Explore_Z::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();

  //process the subgoals
  m_iStatus = ProcessSubgoals();

  return m_iStatus;
}


//---------------------------- HandleMessage ----------------------------------
//-----------------------------------------------------------------------------
bool Goal_Explore_Z::HandleMessage(const Telegram& msg)
{
  //first, pass the message down the goal hierarchy
  bool bHandled = ForwardMessageToFrontMostSubgoal(msg);

  //if the msg was not handled, test to see if this goal can handle it
  if (bHandled == false)
  {
    switch(msg.Msg)
    {
    case Msg_PathReady:

      //clear any existing goals
      RemoveAllSubgoals();

      AddSubgoal(new Goal_FollowPath_Z(m_pOwner,
                                     m_pOwner->GetPathPlanner()->GetPath()));

      return true; //msg handled


    case Msg_NoPathAvailable:

      m_iStatus = failed;

      return true; //msg handled

    default: return false;
    }
  }

  //handled by subgoals
  return true;
}




