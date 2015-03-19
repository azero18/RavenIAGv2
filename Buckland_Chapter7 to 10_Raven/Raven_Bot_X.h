#ifndef RAVEN_BOTX_H
#define RAVEN_BOTX_H
#pragma warning (disable:4786)
#include "Raven_Bot.h"

class Raven_Bot_X : public Raven_Bot 
{
private:

  //bots shouldn't be copied, only created or respawned
  Raven_Bot_X(const Raven_Bot&);
  Raven_Bot_X& operator=(const Raven_Bot_X&);

public:
  
  Raven_Bot_X(Raven_Game* world, Vector2D pos);
  virtual ~Raven_Bot_X();

  //the usual suspects
  void         Render();

};




#endif