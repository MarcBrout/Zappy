//
// Created by brout_m on 26/06/17.
//

#ifndef ZAPPY_AILOGIC_HPP
#define ZAPPY_AILOGIC_HPP

#include <map>
#include <vector>
#include "tools/Splitter.hpp"
#include "core_ai/CoreAI.hpp"

namespace zappy
{
  class Core;

  class AILogic : public CoreAI
  {
  public:
    typedef bool (AILogic::*condPtr)();
    typedef bool (AILogic::*actionPtr)();

    typedef std::vector<std::uint32_t> inventory_t;
    typedef std::vector<std::string>   look_t;

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
    void run();
    bool isIncantating() const;
    bool startedImcatation() const;

  private:
    STATE m_state;
    std::map<STATE, std::vector<std::pair<condPtr, actionPtr>>> m_logic;
    Splitter    m_splitter;
    std::vector<std::pair<std::string, bool>> m_search;
    look_t      m_look;
    bool        m_directObj;
    std::size_t m_fullLine;
    std::size_t m_fullTurn;
    std::size_t m_curLvl;
    std::size_t m_id;
    std::size_t m_trackId;
    std::size_t m_dir;
    bool        m_needFood;
    bool        m_incant;
    bool        m_startedIncantation;
    int         m_timeout;
    std::string m_searchings;
    std::uint32_t m_nbObj;
    std::uint32_t m_playerStayedFor;

    inventory_t getInventory(std::string const &inventory);
    void getLook(std::string const &);
    bool wasWaiting();
    bool stopBroadcast();

    void fillInitialState();
    bool needFood();
    bool searchFood();
    bool wasOnWaitingState();
    bool goToWaitingState();
    bool wasOnJoinningState();
    bool goToJoinningState();
    bool receivedHelp();
    bool initJoinningState();
    bool wasOnSearchingState();
    bool goToSearchingState();
    bool canIFork();
    bool goFork();
    bool missingObject();
    bool searchObject();

    void fillSearchState();
    bool objOnCase();
    bool objOnSight();
    bool isNotFullTurn();
    bool isFullLine();
    bool finalForward();
    bool look();
    bool turnSearch();
    bool TurnGoTurn();
    bool goSearch();
    bool takeObj();

    void fillJoinState();
    bool timeOut();
    bool resetJoiningState();
    bool receivedBroadcastHelp();
    bool isArrived();
    bool receivedBroadcastStop();
    bool endJoin();
    bool finalForwardJoin();

    void fillPassiveState();
    bool incantFailed();
    bool sendStop();
    bool broadcastSuccess();
    bool updateLvl();
    bool passiveToInitial();
    bool turnPass();
    bool broadcastStopPass();
    bool checkContent();
    bool pickUpObject();

    void fillActiveState();
    bool missingPlayer();
    bool broadcastHelpActive();
    bool adjustResources();
    bool incantation();
  };
}

#endif // ZAPPY_AILOGIC_HPP
