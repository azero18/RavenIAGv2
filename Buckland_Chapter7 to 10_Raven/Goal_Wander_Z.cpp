#include "Goal_Wander_Z.h"
#include "Raven_Bot_Z.h"
#include "Raven_SteeringBehaviors.h"





//---------------------------- Initialize -------------------------------------
//-----------------------------------------------------------------------------  
void Goal_Wander_Z::Activate()
{
  m_iStatus = active;

  m_pOwner->GetSteering()->WanderOn();
}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_Wander_Z::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();

  return m_iStatus;
}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_Wander_Z::Terminate()
{
  m_pOwner->GetSteering()->WanderOff();
}

