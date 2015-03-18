#ifndef GOAL_EVALUATORZ_H
#define GOAL_EVALUATORZ_H
#pragma warning (disable : 4786)

class Raven_Bot_Z;
struct Vector2D;


class Goal_Evaluator_Z
{
protected:

  //when the desirability score for a goal has been evaluated it is multiplied 
  //by this value. It can be used to create bots with preferences based upon
  //their personality
  double       m_dCharacterBias;

public:

  Goal_Evaluator_Z(double CharacterBias):m_dCharacterBias(CharacterBias){}
  
  virtual ~Goal_Evaluator_Z(){}
  
  //returns a score between 0 and 1 representing the desirability of the
  //strategy the concrete subclass represents
  virtual double CalculateDesirability(Raven_Bot_Z* pBot)=0;
  
  //adds the appropriate goal to the given bot's brain
  virtual void  SetGoal(Raven_Bot_Z* pBot) = 0;

  //used to provide debugging/tweaking support
  virtual void  RenderInfo(Vector2D Position, Raven_Bot_Z* pBot) = 0;
};




#endif

