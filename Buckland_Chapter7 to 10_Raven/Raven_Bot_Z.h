#ifndef RAVEN_BOTZ_H
#define RAVEN_BOTZ_H
#pragma warning (disable:4786)

#include "Raven_Bot.h"

class Goal_Think_Z;

class Raven_Bot_Z : public Raven_Bot
{
	
public:

	Raven_Bot_Z(Raven_Game* world, Vector2D pos);
	virtual ~Raven_Bot_Z();

	void Render();

};

#endif