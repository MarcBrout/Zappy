//
// Created by brout_m on 26/06/17.
//

#include <algorithm>
#include "ai_logic/AILogic.hpp"

namespace zappy
{
  AILogic::~AILogic()
  {
  }

  AILogic::AILogic(Core &core)
      : CoreAI(core), m_state(AILogic::STATE::INITIAL), m_logic(),
        m_splitter(), m_search(""), m_look(), m_directObj(false),
        m_fullLine(0), m_fullTurn(0), m_curLvl(1),
        m_id(static_cast<std::size_t>(std::rand())), m_trackId(0), m_dir(1)
  {
    fillSearchState();
    fillJoinState();
    fillPassiveState();
    fillActiveState();
  }

  void AILogic::run()
  {
    if (needFood())
      {
	m_search = "food";
	if (wasWaiting())
	  {
	    stopBroadcast();
	  }
	else
	  {
	    look();
	    std::vector<std::pair<condPtr, actionPtr>> vec(
	        m_logic[STATE::SEARCHING]);
	    std::vector<std::pair<condPtr, actionPtr>>::iterator it;

	    for (it = vec.begin(); it != vec.end(); ++it)
	      {
		if ((this->*(it->first))())
		  {
		    (this->*(it->second))();
		    break;
		  }
	      }
	  }
      }
    else
      {
	std::vector<std::pair<condPtr, actionPtr>> vec(m_logic[m_state]);
	std::vector<std::pair<condPtr, actionPtr>>::iterator it;

	for (it = vec.begin(); it != vec.end(); ++it)
	  {
	    if ((this->*(it->first))())
	      {
		(this->*(it->second))();
		break;
	      }
	  }
	if (it == vec.end())
	  {
	    switch (m_state)
	      {
	      case STATE::INITIAL:
		break;
	      case STATE::SEARCHING:
		finalForward();
		break;
	      case STATE::JOINING:
		finalForwardJoin();
		break;
	      case STATE::ACTIVE_WAITING:
		takeObjActive();
		break;
	      case STATE::PASSIVE_WAITING:
		turnPass();
		break;
	      default:
		break;
	      }
	  }
	_message.clear();
	_response.clear();
      }
  }

  void AILogic::getLook(std::string const &look)
  {
    m_splitter.clear();
    m_splitter.split(look, "[,]", false);
    m_splitter.moveTokensTo(m_look);
  }

  bool AILogic::needFood()
  {
    sendActionAndCheckResponse(ACTION::INVENTORY, "", 1, {});
    inventory_t inventory = getInventory(_response[0]);
    return (inventory[OBJECTS::FOOD] < 10);
  }

  AILogic::inventory_t AILogic::getInventory(std::string const &inventory)
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
	    values[i] = std::stol(rawValues[i].substr(pos + 1));
	  }
      }
    return values;
  }

  void AILogic::fillSearchState()
  {
    std::vector<std::pair<condPtr, actionPtr>> searchVec;

    searchVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::objOnCase, &zappy::AILogic::takeObj));
    searchVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::objOnSight, &zappy::AILogic::goSearch));
    searchVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::isNotFullTurn, &zappy::AILogic::turnSearch));
    searchVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::isFullLine, &zappy::AILogic::TurnGoTurn));
    m_logic[STATE::SEARCHING] = searchVec;
  }

  bool AILogic::finalForward()
  {
    sendActionAndCheckResponse(ACTION::FORWARD, "Forward", 1, {});
    ++m_fullLine;
    return true;
  }

  bool AILogic::takeObj()
  {
    sendActionAndCheckResponse(ACTION::TAKE, m_search, 1, {});
    m_state = STATE::INITIAL;
    return true;
  }

  bool AILogic::goSearch()
  {
    if (!m_directObj)
      {
	sendActionAndCheckResponse(ACTION::FORWARD, "Forward", 1, {});
      }
    m_fullLine = 0;
    m_fullTurn = 0;
    m_directObj = false;
    return true;
  }

  static const std::pair<std::string, std::size_t> caseFullLine[8] = {
      {"Left\nForward\nForward\nForward\nRight", 5},
      {"Left\nForward\nForward\nForward\nForward\nForward\nRight", 7},
      {"Left\nForward\nForward\nForward\nForward\nForward\nForward\nForward\nR"
       "ight",
       9},
      {"Left\nForward\nForward\nForward\nForward\nForward\nForward\nForward\nF"
       "orward\nRight",
       10},
      {"Left\nForward\nForward\nForward\nForward\nForward\nForward\nForward\nF"
       "orward\nRight",
       10},
      {"Left\nForward\nForward\nForward\nForward\nForward\nForward\nForward\nF"
       "orward\nRight",
       10},
      {"Left\nForward\nForward\nForward\nForward\nForward\nForward\nForward\nF"
       "orward\nRight",
       10},
      {"Left\nForward\nForward\nForward\nForward\nForward\nForward\nForward\nF"
       "orward\nRight",
       10}};

  bool AILogic::TurnGoTurn()
  {
    sendActionAndCheckResponse(
        ACTION::RAW, caseFullLine[m_curLvl].first,
        static_cast<std::uint32_t>(caseFullLine[m_curLvl].second), {});
    return true;
  }

  bool AILogic::turnSearch()
  {
    sendActionAndCheckResponse(ACTION::LEFT, "Left", 1, {});
    ++m_fullTurn;
    return false;
  }

  bool AILogic::look()
  {
    sendActionAndCheckResponse(ACTION::LOOK, "", 1, {});
    getLook(_response[0]);
    return true;
  }

  bool AILogic::isFullLine()
  {
    if (_pos.x > _pos.y && m_fullLine == _pos.x)
      {
	m_fullLine = 0;
	return true;
      }
    else if (_pos.x <= _pos.y && m_fullLine == _pos.y)
      {
	m_fullLine = 0;
	return true;
      }
    return false;
  }

  bool AILogic::isNotFullTurn()
  {
    if (m_fullTurn == 4)
      {
	m_fullTurn = 0;
	++m_fullLine;
	return false;
      }
    return true;
  }

  static const std::pair<std::string, std::size_t> caseAction[10] = {
      {"", 0},
      {"Forward\nLeft\nForward", 3},
      {"Forward", 1},
      {"Forward\nRight\nForward", 3},
      {"Forward\nForward\nLeft\nForward\nForward", 5},
      {"Forward\nForward\nLeft\nForward", 4},
      {"Forward\nForward", 2},
      {"Forward\nForward\nRight\nForward", 4},
      {"Forward\nForward\nRight\nForward\nForward", 5}};

  bool AILogic::objOnSight()
  {
    std::size_t caseIdx(0);
    bool        playerInCase(false);
    bool        objInCase(false);

    for (std::string cas : m_look)
      {
	m_splitter.clear();
	m_splitter.split(cas, " ", false);
	std::vector<std::string> objs;
	m_splitter.moveTokensTo(objs);
	for (std::string obj : objs)
	  {
	    if (obj == m_search)
	      {
		objInCase = true;
	      }
	    if (obj == "player")
	      {
		playerInCase = true;
	      }
	  }
	if (objInCase && !playerInCase)
	  {
	    if (caseIdx < 9)
	      {
		sendActionAndCheckResponse(
		    ACTION::RAW, caseAction[caseIdx].first,
		    static_cast<std::uint32_t>(caseAction[caseIdx].second),
		    {});
		m_directObj = true;
	      }
	    return true;
	  }
	objInCase = false;
	playerInCase = false;
	++caseIdx;
      }
    return false;
  }

  bool AILogic::objOnCase()
  {
    std::string objInCase = m_look[1];
    m_splitter.clear();
    m_splitter.split(objInCase, " ", false);
    std::vector<std::string> objs;
    m_splitter.moveTokensTo(objs);
    int  playerInCase(0);
    bool objFind(false);

    for (std::string obj : objs)
      {
	if (obj == m_search)
	  {
	    objFind = true;
	  }
	if (obj == "player")
	  {
	    playerInCase++;
	  }
      }
    return (objFind && playerInCase < 2);
  }

  void AILogic::fillJoinState()
  {
    std::vector<std::pair<condPtr, actionPtr>> joinVec;

    joinVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::receivedBroadcastHelp, &zappy::AILogic::isArrived));
    joinVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::receivedBroadcastStop, &zappy::AILogic::endJoin));
    m_logic[STATE::JOINING] = joinVec;
  }

  bool AILogic::receivedBroadcastHelp()
  {
    std::vector<std::string> vecInfo;
    std::string              text;

    for (std::string msg : _message)
      {
	if (msg.substr(0, 7) == "message")
	  {
	    text = msg.substr(msg.find(',') + 1);
	    m_splitter.clear();
	    m_splitter.split(text, " ", false);
	    m_splitter.moveTokensTo(vecInfo);
	    if (std::stoi(vecInfo[0]) == m_trackId &&
	        std::stoi(vecInfo[1]) == m_curLvl && vecInfo[2] == "HELP")
	      {
		m_dir = static_cast<std::size_t>(std::stoi(msg.substr(8, 1)));
		return true;
	      }
	  }
      }
    return false;
  }

  bool AILogic::finalForwardJoin()
  {
    sendActionAndCheckResponse(ACTION::FORWARD, "Forward", 1, {});
    return true;
  }

  bool AILogic::receivedBroadcastStop()
  {
    std::vector<std::string> vecInfo;
    std::string              text;

    for (std::string msg : _message)
      {
	if (msg.substr(0, 7) == "message")
	  {
	    text = msg.substr(msg.find(',') + 1);
	    m_splitter.clear();
	    m_splitter.split(text, " ", false);
	    m_splitter.moveTokensTo(vecInfo);
	    if (std::stoi(vecInfo[0]) == m_trackId &&
	        std::stoi(vecInfo[1]) == m_curLvl && vecInfo[2] == "STOP")
	      {
		return true;
	      }
	  }
      }
    return false;
  }

  static const std::pair<std::string, std::size_t> joinCaseMove[9] = {
      {"", 0},
      {"Forward", 1},
      {"Forward\nLeft\nForward", 3},
      {"Left\nForward", 2},
      {"Left\nForward\nLeft\nForward", 4},
      {"Left\nLeft\nForward", 3},
      {"Right\nForward\nRight\nForward", 4},
      {"Right\nForward", 2},
      {"Forward\nRight\nForward", 3}};

  bool AILogic::isArrived()
  {
    if (m_dir == 0)
      {
	joinToPass();
      }
    else
      {
	sendActionAndCheckResponse(
	    ACTION::RAW, joinCaseMove[m_dir].first,
	    static_cast<std::uint32_t>(joinCaseMove[m_dir].second), {});
      }
    return true;
  }

  bool AILogic::joinToPass()
  {
    m_state = STATE::PASSIVE_WAITING;
    return true;
  }

  bool AILogic::endJoin()
  {
    m_state = STATE::INITIAL;
    return true;
  }

  void AILogic::fillPassiveState()
  {
    std::vector<std::pair<condPtr, actionPtr>> passiveVec;

    passiveVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::broadcastSuccess, &zappy::AILogic::updateLvl));
    passiveVec.push_back(
        std::make_pair<condPtr, actionPtr>(&zappy::AILogic::broadcastStopPass,
                                           &zappy::AILogic::passiveToInitial));
    passiveVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::checkContent, &zappy::AILogic::pickUpObject));
    m_logic[STATE::PASSIVE_WAITING] = passiveVec;
  }

  bool AILogic::broadcastSuccess()
  {
    bool levelUp = false;

    if (std::for_each(_message.begin(), _message.end(),
                      [&levelUp, this](std::string const &str) {
                        if (str.substr(0, str.find(":")) == "Current level")
	                  {
	                    long lvl = std::stol(
	                        str.substr(str.find(": ") + 1, str.length()));
	                    levelUp = lvl > this->m_curLvl;
	                  };
                      }))
      ;
    return levelUp;
  }

  bool AILogic::updateLvl()
  {
    ++m_curLvl;
    return true;
  }

  bool AILogic::passiveToInitial()
  {
    m_trackId = 0;
    m_state = STATE::INITIAL;
    return true;
  }

  bool AILogic::turnPass()
  {
    sendActionAndCheckResponse(ACTION::LEFT, "", 0, {});
    return true;
  }

      static const std::vector<std::vector<std::uint32_t>> gl_incantations =
          {
              {1, 1, 0, 0, 0, 0, 0},
              {2, 1, 1, 1, 0, 0, 0},
              {2, 2, 0, 1, 0, 2, 0},
              {4, 1, 1, 2, 0, 1, 0},
              {4, 1, 2, 1, 3, 0, 0},
              {6, 1, 2, 3, 0, 1, 0},
              {6, 2, 2, 2, 2, 2, 1}
          };

      static const std::vector<std::string> names =
          {"player", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

  bool AILogic::checkContent()
  {
    bool caseClean = true;

    sendActionAndCheckResponse(ACTION::LOOK, "", 0, {});
    m_splitter.clear();
    m_splitter.split(_response[0], "[,]");

    std::vector<std::string> cells;
    m_splitter.moveTokensTo(cells);

    m_splitter.clear();
    m_splitter.split(cells[1], " ");



    return caseClean;
  }

  bool AILogic::pickUpObject()
  {
    return false;
  }

  bool AILogic::broadcastStopPass()
  {
    bool stop = false;

    if (std::for_each(_message.begin(), _message.end(),
                      [&stop, this](std::string const &str) {
                        if (str.find("message ") != std::string::npos)
	                  {
	                    m_splitter.clear();
	                    m_splitter.split(str, ",");
	                    std::vector<std::string> prefix;

	                    m_splitter.moveTokensTo(prefix);
	                    int dir = std::stoi(
	                        prefix[0].substr(prefix[0].find(" ")));

	                    m_splitter.clear();
	                    m_splitter.split(prefix[1], " ");
	                    std::vector<std::string> message;
	                    if (!dir && std::stoi(message[0]) == m_trackId &&
	                        std::stoi(message[1]) == m_curLvl)
	                      stop = message[2] == "STOP";
	                  };
                      }))
      ;
    return stop;
  }

  void AILogic::fillActiveState()
  {
    std::vector<std::pair<condPtr, actionPtr>> activeVec;

    activeVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::missingPlayer, &zappy::AILogic::broadcastHelpActive));
    activeVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::needDrop, &zappy::AILogic::dropObjActive));
    activeVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::notNeedResource, &zappy::AILogic::incantation));
    m_logic[STATE::ACTIVE_WAITING] = activeVec;
  }

  bool AILogic::missingPlayer()
  {
    std::size_t nbPlayer(0);
    std::size_t countNbPlayer(0);

    look();
    switch (m_curLvl)
      {
      case 1:
	nbPlayer = 1;
	break;
      case 2:
      case 3:
	nbPlayer = 2;
	break;
      case 4:
      case 5:
	nbPlayer = 4;
	break;
      case 6:
      case 7:
	nbPlayer = 6;
	break;
      default:
	break;
      }
    for (std::string inCase : m_look)
      {
	if (inCase == "player")
	  ++countNbPlayer;
      }
    return nbPlayer > countNbPlayer;
  }

  bool AILogic::needDrop()
  {
    return false;
  }

  bool AILogic::broadcastHelpActive()
  {
    sendActionAndCheckResponse(ACTION::BROADCAST,
                               std::to_string(m_id) + " " +
                                   std::to_string(m_curLvl) + " HELP",
                               1, {});
    std::vector<std::uint32_t> nbObjInCase;
    nbObjInCase.resize(7);

    nbObjInCase[0] = gl_incanation[m_curLvl - 1][0];
    std::vector<std::string>   typeObjInCase;
    m_splitter.clear();
    m_splitter.split(m_look[0], " ", false);
    m_splitter.moveTokensTo(typeObjInCase);
    for (std::string typeObj : typeObjInCase)
    {
        if (typeObj == "linemate")
            ++nbObjInCase[OBJECTS::LINEMATE];
        else if (typeObj == "deraumere")
            ++nbObjInCase[OBJECTS::DERAUMERE];
        else if (typeObj == "sibur")
            ++nbObjInCase[OBJECTS::SIBUR];
        else if (typeObj == "mendiane")
            ++nbObjInCase[OBJECTS::MENDIANE];
        else if (typeObj == "phiras")
            ++nbObjInCase[OBJECTS::PHIRAS];
        else if (typeObj == "thystame")
            ++nbObjInCase[OBJECTS::THYSTAME];
    }
      if (nbObjInCase == gl_incantations[m_curLvl - 1])
      {
         return true;
      }
      else
      {
        std::string needed;
      }
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

  bool AILogic::takeObjActive()
  {
    return false;
  }

  bool AILogic::wasWaiting()
  {
    return m_state == STATE::ACTIVE_WAITING;
  }

  bool AILogic::stopBroadcast()
  {
    return false;
  }
}
