#include "Goal_GetItem_Z.h"
#include "Raven_ObjectEnumerations.h"
#include "Raven_Bot_Z.h"
#include "navigation/Raven_PathPlanner.h"

#include "Messaging/Telegram.h"
#include "Raven_Messages.h"

#include "Goal_Wander_Z.h"
#include "Goal_FollowPath_Z.h"


int ItemTypeToGoalType_Z(int gt)
{
  switch(gt)
  {
  case type_health:

    return goal_get_health_Z;

  case type_shotgun:

    return goal_get_shotgun_Z;

  case type_rail_gun:

    return goal_get_railgun_Z;

  case type_rocket_launcher:

    return goal_get_rocket_launcher_Z;

  default: throw std::runtime_error("Goal_GetItem cannot determine item type");

  }//end switch
}

//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_GetItem_Z::Activate()
{
  m_iStatus = active;
  
  m_pGiverTrigger = 0;
  
  //request a path to the item
  m_pOwner->GetPathPlanner()->RequestPathToItem(m_iItemToGet);

  //the bot may have to wait a few update cycles before a path is calculated
  //so for appearances sake it just wanders
  AddSubgoal(new Goal_Wander_Z(m_pOwner));

}

//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Goal_GetItem_Z::Process()
{
  ActivateIfInactive();

  if (hasItemBeenStolen())
  {
    Terminate();
  }

  else
  {
    //process the subgoals
    m_iStatus = ProcessSubgoals();
  }

  return m_iStatus;
}
//---------------------------- HandleMessage ----------------------------------
//-----------------------------------------------------------------------------
bool Goal_GetItem_Z::HandleMessage(const Telegram& msg)
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

      //get the pointer to the item
	  m_pGiverTrigger = static_cast<Trigger<Raven_Bot_Z>*>(msg.ExtraInfo);      

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

//---------------------------- hasItemBeenStolen ------------------------------
//
//  returns true if the bot sees that the item it is heading for has been
//  picked up by an opponent
//-----------------------------------------------------------------------------
bool Goal_GetItem_Z::hasItemBeenStolen()const
{
  if (m_pGiverTrigger &&
      !m_pGiverTrigger->isActive() &&
      m_pOwner->hasLOSto(m_pGiverTrigger->Pos()) )
  {
    return true;
  }

  return false;
}