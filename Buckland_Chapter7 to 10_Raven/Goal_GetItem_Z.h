#ifndef GOAL_GET_ITEMZ_H
#define GOAL_GET_ITEMZ_H
#pragma warning (disable:4786)

#include "Goal_Composite_Z.h"
#include "goals/Raven_Goal_Types.h"
#include "Raven_Bot_Z.h"
#include "triggers/trigger.h"


//helper function to change an item type enumeration into a goal type
int ItemTypeToGoalType_Z(int gt);


class Goal_GetItem_Z : public Goal_Composite_Z<Raven_Bot_Z>
{
private:

  int                     m_iItemToGet;

  Trigger<Raven_Bot_Z>*     m_pGiverTrigger;

  //true if a path to the item has been formulated
  bool                    m_bFollowingPath;

  //returns true if the bot sees that the item it is heading for has been
  //picked up by an opponent
  bool hasItemBeenStolen()const;

public:

  Goal_GetItem_Z(Raven_Bot_Z* pBot,
               int        item):Goal_Composite_Z<Raven_Bot_Z>(pBot,
                                                   ItemTypeToGoalType_Z(item)),
                                m_iItemToGet(item),
                                m_pGiverTrigger(0),
                                m_bFollowingPath(false)
  {}


  void Activate();

  int  Process();

  bool HandleMessage(const Telegram& msg);

  void Terminate(){m_iStatus = completed;}
};






#endif
