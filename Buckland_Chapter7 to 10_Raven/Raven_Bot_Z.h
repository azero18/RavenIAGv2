#ifndef RAVEN_BOTZ_H
#define RAVEN_BOTZ_H
#pragma warning (disable:4786)
#include "Raven_Bot.h"

class Raven_Bot_Z : public Raven_Bot
{
private:

  //bots shouldn't be copied, only created or respawned
  Raven_Bot_Z(const Raven_Bot&);
  Raven_Bot_Z& operator=(const Raven_Bot_Z&);

public:
  
  Raven_Bot_Z(Raven_Game* world, Vector2D pos);
  virtual ~Raven_Bot_Z();

  //the usual suspects
  void         Render();

};
#endif