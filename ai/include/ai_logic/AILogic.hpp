//
// Created by brout_m on 26/06/17.
//

#ifndef ZAPPY_AILOGIC_HPP
#define ZAPPY_AILOGIC_HPP

#include <map>
#include <vector>
#include "tools/Splitter.hpp"

namespace zappy
{
  class CoreAI;
  class Core;

  class AILogic : public CoreAI
  {
    typedef bool (AILogic::*condPtr)();
    typedef bool (AILogic::*          actionPtr)();
    typedef std::vector<std::int64_t> inventory_t;

  public:
    enum STATE
    {
      INITIAL,
      SEARCHING,
      JOINING,
      PASSIVE_WAITING,
      ACTIVE_WAITING
    };

    enum OBJECTS
    {
      FOOD,
      LINEMATE,
      DERAUMERE,
      SIBUR,
      MENDIANE,
      PHIRAS,
      THYSTAME
    };

    AILogic(Core &core);
    virtual ~AILogic();

  private:
    STATE m_state;
    std::map<STATE, std::vector<std::pair<condPtr, actionPtr>>> m_logic;
    Splitter m_splitter;

    bool                      needFood();
    inventory_t getInventory(std::string const &inventory);

    void fillSearchState();
    bool objOnCase();
    bool objOnSight();
    bool isNotFullTurn();
    bool isFullLine();
    bool peopleSameCase();
    bool peopleSameSight();
    bool look();
    bool turnSearch();
    bool TurnGoTurn();
    bool goSearch();
    bool takeObj();

    void fillJoinState();
    bool broadcastHelp();
    bool broadcastStop();
    bool isArrived();
    bool joinToPass();
    bool isDir();
    bool endJoin();
    bool goJoin();
    bool turnThenGo();

    void fillPassiveState();
    bool broadcastSuccess();
    bool updateLvl();
    bool passiveToInitial();
    bool turnPass();
    bool broadcastStopPass();
    bool passEnd();

    void fillActiveState();
    bool missingPlayer();
    bool needDrop();
    bool broadcastHelpActive();
    bool dropObjActive();
    bool notNeedResource();
    bool incantation();
  };
}

#endif // ZAPPY_AILOGIC_HPP
