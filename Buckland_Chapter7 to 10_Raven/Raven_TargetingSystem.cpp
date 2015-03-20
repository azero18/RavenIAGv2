#include "Raven_TargetingSystem.h"
#include "Raven_Bot.h"
#include "Raven_SensoryMemory.h"
#include "goals/Goal_Think.h"
#include "goals/Raven_Goal_Types.h"
#include "goals/Raven_Feature.h"


//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Raven_TargetingSystem::Raven_TargetingSystem(Raven_Bot* owner):m_pOwner(owner),
                                                               m_pCurrentTarget(0)
{}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void Raven_TargetingSystem::Update()
{
  double ClosestDistSoFar = MaxDouble;
  m_pCurrentTarget       = 0;

  //grab a list of all the opponents the owner can sense
  std::list<Raven_Bot*> SensedBots;
  SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();
  //NEW
  int think_type = m_pOwner->GetBrain()->GetType();

  if (think_type == goal_think)
  {
	  std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
	  for (curBot; curBot != SensedBots.end(); ++curBot)
	  {
		//make sure the bot is alive and that it is not the owner
		if ((*curBot)->isAlive() && (*curBot != m_pOwner) )
		{
		  double dist = Vec2DDistanceSq((*curBot)->Pos(), m_pOwner->Pos());

		  if (dist < ClosestDistSoFar)
		  {
			ClosestDistSoFar = dist;
			m_pCurrentTarget = *curBot;
		  }
		}
	  }
  }
  //NEW: aplicar heuristica do dano estimado
  if (think_type == goal_think_Z)
  {
	  //ClosestDistSoFar = 0;

	  double RailgunStrenght = Raven_Feature::IndividualWeaponStrength(m_pOwner,type_rail_gun);
	  double ShotgunStrenght = Raven_Feature::IndividualWeaponStrength(m_pOwner,type_shotgun);
	  double RocketStrenght = Raven_Feature::IndividualWeaponStrength(m_pOwner, type_rocket_launcher);
	  
	  double distMod;
		  if ((RailgunStrenght > ShotgunStrenght)||(RocketStrenght > ShotgunStrenght))
		  {
			distMod = ((RailgunStrenght+RocketStrenght)/2)+ShotgunStrenght;
		  }else
		  {
		    distMod = ShotgunStrenght;
		  }

	  std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
	  for (curBot; curBot != SensedBots.end(); ++curBot)
	  {
		//make sure the bot is alive and that it is not the owner
		if ((*curBot)->isAlive() && (*curBot != m_pOwner) )
		{	  

		  double dist = Vec2DDistance((*curBot)->Pos(), m_pOwner->Pos());

		  double tdist = dist*distMod;

		  int estimedHealth = (100 - m_pOwner->GetSensoryMem()->getEDMG(*curBot))/100;

		  double calculus = tdist / estimedHealth;

		  if (calculus < ClosestDistSoFar)
		  {
			ClosestDistSoFar = calculus;
			m_pCurrentTarget = *curBot;
		  }
		}
	  }
  }
}




bool Raven_TargetingSystem::isTargetWithinFOV()const
{
  return m_pOwner->GetSensoryMem()->isOpponentWithinFOV(m_pCurrentTarget);
}

bool Raven_TargetingSystem::isTargetShootable()const
{
  return m_pOwner->GetSensoryMem()->isOpponentShootable(m_pCurrentTarget);
}

Vector2D Raven_TargetingSystem::GetLastRecordedPosition()const
{
  return m_pOwner->GetSensoryMem()->GetLastRecordedPositionOfOpponent(m_pCurrentTarget);
}

double Raven_TargetingSystem::GetTimeTargetHasBeenVisible()const
{
  return m_pOwner->GetSensoryMem()->GetTimeOpponentHasBeenVisible(m_pCurrentTarget);
}

double Raven_TargetingSystem::GetTimeTargetHasBeenOutOfView()const
{
  return m_pOwner->GetSensoryMem()->GetTimeOpponentHasBeenOutOfView(m_pCurrentTarget);
}
