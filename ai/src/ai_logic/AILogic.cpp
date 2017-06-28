//
// Created by brout_m on 26/06/17.
//

#include "core_ai/CoreAI.hpp"

namespace zappy
{
  AILogic::~AILogic()
  {
  }

  AILogic::AILogic(Core &core)
      : CoreAI(core), m_state(AILogic::STATE::INITIAL), m_logic(), m_splitter()
  {
    fillSearchState();
    fillJoinState();
    fillPassiveState();
    fillActiveState();
  }

  void AILogic::fillSearchState()
  {
    std::vector<std::pair<condPtr, actionPtr>> searchVec;

    searchVec.push_back(
        std::pair(&zappy::AILogic::objOnCase, &zappy::AILogic::takeObj));
    searchVec.push_back(
        std::pair(&zappy::AILogic::objOnSight, &zappy::AILogic::goSearch));
    searchVec.push_back(std::pair(&zappy::AILogic::isNotFullTurn,
                                  &zappy::AILogic::turnSearch));
    searchVec.push_back(
        std::pair(&zappy::AILogic::isFullLine, &zappy::AILogic::TurnGoTurn));
    m_logic[STATE::SEARCHING] = searchVec;
  }

  bool AILogic::takeObj()
  {
    return !peopleSameCase();
  }

  bool AILogic::goSearch()
  {
    return !peopleSameSight();
  }

  bool AILogic::TurnGoTurn()
  {
    return false;
  }

  bool AILogic::turnSearch()
  {
    return false;
  }

  bool AILogic::look()
  {
    return false;
  }

  bool AILogic::peopleSameSight()
  {
    return false;
  }

  bool AILogic::peopleSameCase()
  {
    return false;
  }

  bool AILogic::isFullLine()
  {
    return false;
  }

  bool AILogic::isNotFullTurn()
  {
    return false;
  }

  bool AILogic::objOnSight()
  {
    return false;
  }

  bool AILogic::objOnCase()
  {
    return false;
  }

  void AILogic::fillJoinState()
  {
    std::vector<std::pair<condPtr, actionPtr>> joinVec;

    joinVec.push_back(
        std::pair(&zappy::AILogic::broadcastHelp, &zappy::AILogic::isArrived));
    joinVec.push_back(
        std::pair(&zappy::AILogic::broadcastStop, &zappy::AILogic::endJoin));
    joinVec.push_back(
        std::pair(&zappy::AILogic::isArrived, &zappy::AILogic::joinToPass));
    joinVec.push_back(
        std::pair(&zappy::AILogic::isDir, &zappy::AILogic::goJoin));
    m_logic[STATE::JOINING] = joinVec;
  }

  bool AILogic::broadcastHelp()
  {
    return false;
  }

  bool AILogic::broadcastStop()
  {
    return false;
  }

  bool AILogic::isArrived()
  {
    return false;
  }

  bool AILogic::joinToPass()
  {
    return false;
  }

  bool AILogic::isDir()
  {
    return false;
  }

  bool AILogic::endJoin()
  {
    return false;
  }

  bool AILogic::goJoin()
  {
    return false;
  }

  bool AILogic::turnThenGo()
  {
    return false;
  }

  void AILogic::fillPassiveState()
  {
    std::vector<std::pair<condPtr, actionPtr>> passiveVec;

    passiveVec.push_back(std::pair(&zappy::AILogic::broadcastSuccess,
                                   &zappy::AILogic::updateLvl));
    passiveVec.push_back(std::pair(&zappy::AILogic::broadcastStopPass,
                                   &zappy::AILogic::passiveToInitial));
    passiveVec.push_back(
        std::pair(&zappy::AILogic::turnPass, &zappy::AILogic::passEnd));
    m_logic[STATE::PASSIVE_WAITING] = passiveVec;
  }

  bool AILogic::broadcastSuccess()
  {
    return false;
  }

  bool AILogic::updateLvl()
  {
    return false;
  }

  bool AILogic::passiveToInitial()
  {
    return false;
  }

  bool AILogic::passEnd()
  {
    return false;
  }

  bool AILogic::turnPass()
  {
    return true;
  }

  bool AILogic::broadcastStopPass()
  {
    return false;
  }

  void AILogic::fillActiveState()
  {
    std::vector<std::pair<condPtr, actionPtr>> activeVec;

    activeVec.push_back(
        std::pair(&zappy::AILogic::missingPlayer, &broadcastHelpActive));
    activeVec.push_back(
        std::pair(&zappy::AILogic::needDrop, &zappy::AILogic::dropObjActive));
    activeVec.push_back(std::pair(&zappy::AILogic::notNeedResource,
                                  &zappy::AILogic::incantation));
    m_logic[STATE::ACTIVE_WAITING] = activeVec;
  }

  bool AILogic::missingPlayer()
  {
    return false;
  }

  bool AILogic::needDrop()
  {
    return false;
  }

  bool AILogic::broadcastHelpActive()
  {
    return false;
  }

  bool AILogic::dropObjActive()
  {
    return false;
  }

  bool AILogic::notNeedResource()
  {
    return false;
  }

  bool AILogic::incantation()
  {
    return false;
  }

  bool AILogic::needFood()
  {
    sendActionAndCheckResponse(ACTION::INVENTORY, "", 1, {});
    inventory_t inventory = getInventory(_response[0]);
    return (inventory[OBJECTS::FOOD] < 10);
  }

  inventory_t AILogic::getInventory(std::string const &inventory)
  {
    m_splitter.clear();
    m_splitter.split(inventory, "[,]", false);

    std::vector<std::string> rawValues;
    m_splitter.moveTokensTo(rawValues);

    inventory_t values;
    for (std::uint32_t i = 0; i < rawValues.size(); ++i)
      {
	std::uint64_t pos = rawValues[i].find(' ', 0);

	if (rawValues[i] != "")
	  {
	    values[i] = std::stoul(rawValues[i].substr(pos + 1));
	  }
      }
    return values;
  }
}
