#ifndef RAVEN_BOTZ_H
#define RAVEN_BOTZ_H
#pragma warning (disable:4786)

#include "Raven_Bot.h"

class Goal_Think_Z;

class Raven_Bot_Z : public Raven_Bot
{
private:
	Goal_Think_Z* m_pBrain;
public:

	Raven_Bot_Z(Raven_Game* world, Vector2D pos);
	virtual ~Raven_Bot_Z();

	void Spawn(Vector2D pos);

	void Update();

	void Render();

	//ajeitar para ter variavel que guarda um goal_think_z
	Goal_Think_Z* const                  GetBrain(){return m_pBrain;}
};

#endif