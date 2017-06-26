//
// Created by brout_m on 26/06/17.
//

#ifndef ZAPPY_AILOGIC_HPP
#define ZAPPY_AILOGIC_HPP

#include "core_ai/CoreAI.hpp"

namespace zappy
{
  class AILogic : public CoreAI
  {
  public:
    enum STATE
    {
      NONE,
      SEARCHING,
      JOINING,
      PASSIVE_WAITING,
      ACTIVE_WAITING
    };
    AILogic();
    virtual ~AILogic();

  private:
    STATE m_state;

    void forward();
    void turnLeft();
    void turnRight();

  };
}
#endif // ZAPPY_AILOGIC_HPP
