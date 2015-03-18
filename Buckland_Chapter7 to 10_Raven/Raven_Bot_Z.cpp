#include "Raven_Bot_Z.h"
#include "Goal_Think_Z.h"

#include "misc/Cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "Raven_WeaponSystem.h"
#include "Raven_UserOptions.h"
#include "Raven_SensoryMemory.h"
#include "time/Regulator.h"

#include "Raven_ObjectEnumerations.h"

#include "Debug/DebugConsole.h"

Raven_Bot_Z::Raven_Bot_Z(Raven_Game* world, Vector2D pos):
Raven_Bot(world,pos)
{
	SetEntityType(type_bot_modified);	
	m_pBrain = new Goal_Think_Z(this);

}

Raven_Bot_Z::~Raven_Bot_Z()
{
	
}


void Raven_Bot_Z::Spawn(Vector2D pos)
{
	SetSpawnTime(); //NEW: marque a hora que ele "renasceu"
    SetAlive();
    m_pBrain->RemoveAllSubgoals();
    m_pTargSys->ClearTarget();
    SetPos(pos);
    m_pWeaponSys->Initialize();
    RestoreHealthToMaximum();
}

//-------------------------------- Update -------------------------------------
//
void Raven_Bot_Z::Update()
{
  //process the currently active goal. Note this is required even if the bot
  //is under user control. This is because a goal is created whenever a user 
  //clicks on an area of the map that necessitates a path planning request.
  m_pBrain->Process();
  
  //Calculate the steering force and update the bot's velocity and position
  UpdateMovement();

  //if the bot is under AI control but not scripted
  if (!isPossessed())
  {           
    //examine all the opponents in the bots sensory memory and select one
    //to be the current target
    if (m_pTargetSelectionRegulator->isReady())
    {      
      m_pTargSys->Update();
    }

    //appraise and arbitrate between all possible high level goals
    if (m_pGoalArbitrationRegulator->isReady())
    {
       m_pBrain->Arbitrate(); 
    }

    //update the sensory memory with any visual stimulus
    if (m_pVisionUpdateRegulator->isReady())
    {
      m_pSensoryMem->UpdateVision();
    }
  
    //select the appropriate weapon to use from the weapons currently in
    //the inventory
    if (m_pWeaponSelectionRegulator->isReady())
    {       
      m_pWeaponSys->SelectWeapon();       
    }

    //this method aims the bot's current weapon at the current target
    //and takes a shot if a shot is possible
    m_pWeaponSys->TakeAimAndShoot();
  }
}

void Raven_Bot_Z::Render()                                         
{
  //when a bot is hit by a projectile this value is set to a constant user
  //defined value which dictates how long the bot should have a thick red
  //circle drawn around it (to indicate it's been hit) The circle is drawn
  //as long as this value is positive. (see Render)
  m_iNumUpdatesHitPersistant--;


  if (isDead() || isSpawning()) return;
  
  gdi->BluePen();
  
  m_vecBotVBTrans = WorldTransform(m_vecBotVB,
                                   Pos(),
                                   Facing(),
                                   Facing().Perp(),
                                   Scale());

  gdi->ClosedShape(m_vecBotVBTrans);
  
  //draw the head
  gdi->RedBrush();
  gdi->Circle(Pos(), 6.0 * Scale().x);


  //render the bot's weapon
  m_pWeaponSys->RenderCurrentWeapon();

  //render a thick red circle if the bot gets hit by a weapon
  if (m_bHit)
  {
    gdi->ThickRedPen();
    gdi->HollowBrush();
    gdi->Circle(m_vPosition, BRadius()+1);

    if (m_iNumUpdatesHitPersistant <= 0)
    {
      m_bHit = false;
    }
  }

  gdi->TransparentText();
  gdi->TextColor(0,255,0);

  if (UserOptions->m_bShowBotIDs)
  {
    gdi->TextAtPos(Pos().x -10, Pos().y-20, ttos(ID()));
  }

  if (UserOptions->m_bShowBotHealth)
  {
    gdi->TextAtPos(Pos().x-40, Pos().y-5, "H:"+ ttos(Health()));
  }

  if (UserOptions->m_bShowScore)
  {
    gdi->TextAtPos(Pos().x-40, Pos().y+10, "Scr:"+ ttos(Score()));
  }    
}