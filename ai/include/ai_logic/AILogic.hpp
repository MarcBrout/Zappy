//
// Created by brout_m on 26/06/17.
//

#ifndef ZAPPY_AILOGIC_HPP
#define ZAPPY_AILOGIC_HPP

#include <map>
#include <vector>
#include <pair>
#include "core_ai/CoreAI.hpp"

namespace zappy
{
  class AILogic : public CoreAI
  {
      typedef bool (AILogic::*condPtr)();
      typedef bool (AILogic::*actionPtr)();
  public:
    enum STATE
    {
      INITIAL,
      SEARCHING,
      JOINING,
      PASSIVE_WAITING,
      ACTIVE_WAITING
    };
    AILogic();
    virtual ~AILogic();

  private:
    STATE m_state;
    std::map<STATE, std::vector<std::pair<condPtr, actionPtr>>> m_logic;
  };
}
#endif // ZAPPY_AILOGIC_HPP
