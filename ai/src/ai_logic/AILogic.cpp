//
// Created by brout_m on 26/06/17.
//

#include <unistd.h>
#include <algorithm>
#include <iostream>
#include "ai_logic/AILogic.hpp"
#include "tools/Logger.hpp"

namespace zappy
{
  AILogic::~AILogic()
  {
  }

  AILogic::AILogic(Core &core)
      : CoreAI(core), m_state(AILogic::STATE::INITIAL), m_logic(),
        m_splitter(), m_search(), m_look(), m_directObj(false), m_fullLine(0),
        m_fullTurn(0), m_curLvl(1),
        m_id(static_cast<std::size_t>(std::rand())), m_trackId(0), m_dir(1),
        m_needFood(false), m_incant(false), m_startedIncantation(false),
        m_timeout(rand() % 4 + 2), m_searchings(""), m_nbObj(0),
        m_playerStayedFor(0)
  {
    fillInitialState();
    fillSearchState();
    fillJoinState();
    fillPassiveState();
    fillActiveState();
  }

  void AILogic::run()
  {
    std::vector<std::pair<condPtr, actionPtr>>::iterator it;

    Logger::log(Logger::_DEBUG_, "     ======= RUN LEVEL : " +
                                     std::to_string(m_curLvl) + " =======");
    if (!m_incant)
      {
	Logger::log(Logger::_DEBUG_, "[STATE] ENTERING INITIAL STATE");
	for (it = m_logic[STATE::INITIAL].begin();
	     it != m_logic[STATE::INITIAL].end(); ++it)
	  {
	    if ((this->*(it->first))())
	      {
		(this->*(it->second))();
		break;
	      }
	  }
	if (it == m_logic[STATE::INITIAL].end())
	  {
	    Logger::log(Logger::_DEBUG_,
	                "[STATE] ENTERING ACTIVE WAITING STATE");
	    m_state = STATE::ACTIVE_WAITING;
	  }
      }

    if (m_state != STATE::INITIAL)
      {
	for (it = m_logic[m_state].begin(); it != m_logic[m_state].end(); ++it)
	  {
	    if ((this->*(it->first))())
	      {
		(this->*(it->second))();
		break;
	      }
	  }

	if (it == m_logic[m_state].end())
	  {
	    switch (m_state)
	      {
	      case STATE::SEARCHING:
		finalForward();
		break;
	      case STATE::JOINING:
		finalForwardJoin();
		break;
	      case STATE::ACTIVE_WAITING:
		break;
	      case STATE::PASSIVE_WAITING:
		turnPass();
		break;
	      default:
		break;
	      }
	  }
      }
    _response.clear();
  }

  void AILogic::getLook(std::string const &look)
  {
    m_splitter.clear();
    if (look.size())
      {
	m_splitter.split(look, "[,]", false);
	m_splitter.moveTokensTo(m_look);
	if (m_look.size())
	  m_look.erase(m_look.begin());
      }
    else
      {
	m_look = {};
      }
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
	if (rawValues[i].length() > 4)
	  {
	    std::string::size_type pos = rawValues[i].find(" ", 1);
	    if (pos != std::string::npos)
	      {
		values.push_back(static_cast<std::uint32_t>(
		    std::stol(rawValues[i].substr(pos + 1))));
	      }
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
    Logger::log(Logger::_DEBUG_, "[AI] I do a final forward move");
    sendActionAndCheckResponse(ACTION::FORWARD, "", 1, {});
    ++m_fullLine;
    return true;
  }

  bool AILogic::takeObj()
  {
    Logger::log(Logger::_DEBUG_, "[AI] Taking objects");
    sendActionAndCheckResponse(ACTION::RAW, m_searchings, m_nbObj, {});
    m_state = STATE::INITIAL;
    m_searchings = "";
    m_nbObj = 0;
    return true;
  }

  bool AILogic::goSearch()
  {
    Logger::log(Logger::_DEBUG_, "[AI] I saw an object");
    if (!m_directObj)
      {
	sendActionAndCheckResponse(ACTION::FORWARD, "", 1, {});
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
    Logger::log(Logger::_DEBUG_, "[AI] I have to move far away");
    sendActionAndCheckResponse(
        ACTION::RAW, caseFullLine[m_curLvl].first,
        static_cast<std::uint32_t>(caseFullLine[m_curLvl].second), {});
    return true;
  }

  bool AILogic::turnSearch()
  {
    Logger::log(Logger::_DEBUG_, "[AI] I'm Turning to left");
    sendActionAndCheckResponse(ACTION::LEFT, "Left", 1, {});
    ++m_fullTurn;
    return false;
  }

  bool AILogic::look()
  {
    sendActionAndCheckResponse(ACTION::LOOK, "", 1, {});
    if (!_response.empty())
      getLook(_response[0]);
    return true;
  }

  bool AILogic::isFullLine()
  {
    if (_pos.x > _pos.y && m_fullLine == _pos.x)
      {
	Logger::log(Logger::_DEBUG_, "[AI] I did a full line");

	m_fullLine = 0;
	return true;
      }
    else if (_pos.x <= _pos.y && m_fullLine == _pos.y)
      {
	Logger::log(Logger::_DEBUG_, "[AI] I did a full line");
	m_fullLine = 0;
	return true;
      }
    return false;
  }

  bool AILogic::isNotFullTurn()
  {
    if (m_fullTurn == 4)
      {
	Logger::log(Logger::_DEBUG_, "[AI] I did a full turn");
	m_fullTurn = 0;
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

    m_nbObj = 0;
    m_searchings = "";
    for (std::string cas : m_look)
      {
	m_splitter.clear();
	m_splitter.split(cas, " ", false);
	std::vector<std::string> objs;
	m_splitter.moveTokensTo(objs);
	for (std::string obj : objs)
	  {
	    for (std::pair<std::string, bool> &inList : m_search)
	      {
		if (obj == inList.first)
		  {
		    Logger::log(Logger::_DEBUG_,
		                "[AI] Object found : \n\t\tobject: " +
		                    inList.first + "\n\t\tpos " +
		                    std::to_string(caseIdx));
		    objInCase = true;
		  }
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
    Logger::log(Logger::_DEBUG_, "[STATE] ENTERING SEARCHING STATE");
    look();
    if (!m_look.empty())
      {
	m_splitter.clear();
	m_splitter.split(m_look[0], " ", false);
	std::vector<std::string> objs;
	m_splitter.moveTokensTo(objs);
	int  playerInCase(0);
	bool objFind(false);
	bool isFood = m_search.back().first == "food";

	for (std::string obj : objs)
	  {
	    for (std::pair<std::string, bool> &inList : m_search)
	      {
		if (obj == inList.first && !inList.second)
		  {
		    objFind = true;
		    if (m_nbObj)
		      m_searchings += "\n";
		    ++m_nbObj;
		    m_searchings += "Take " + inList.first;
		    if (inList.first != "food")
		      inList.second = true;
		  }
	      }
	    if (obj == "player")
	      {
		++playerInCase;
	      }
	    if ((objFind && !isFood && m_nbObj == m_search.size()) ||
	        m_nbObj == 10)
	      break;
	  }
	return (objFind && playerInCase < 2);
      }
    return (false);
  }

  void AILogic::fillJoinState()
  {
    std::vector<std::pair<condPtr, actionPtr>> joinVec;

    joinVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::timeOut, &zappy::AILogic::resetJoiningState));
    joinVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::receivedBroadcastHelp, &zappy::AILogic::isArrived));
    joinVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::receivedBroadcastStop, &zappy::AILogic::endJoin));
    m_logic[STATE::JOINING] = joinVec;
  }

  bool AILogic::timeOut()
  {
    Logger::log(Logger::_DEBUG_, "[STATE] ENTERING JOINING STATE");
    if (!m_timeout)
      {
	return (true);
      }
    --m_timeout;
    return (false);
  }

  bool AILogic::resetJoiningState()
  {
    Logger::log(Logger::_DEBUG_, "[AI] Timed out, moving on");
    m_state = STATE::INITIAL;
    return (false);
  }

  bool AILogic::receivedBroadcastHelp()
  {
    std::vector<std::string> vecInfo;
    std::string              text;
    std::uint32_t            timeout = 20;

    Logger::log(Logger::_DEBUG_, "[AI] Waiting for help broadcast");
    _message.clear();
    while (_message.empty() && timeout)
      {
	sendActionAndCheckResponse(ACTION::INVENTORY, "", 1, {});
	--timeout;
      }

    for (int i = static_cast<int>(_message.size()) - 1; i >= 0; --i)
      {
	if (_message[i].substr(0, 7) == "message")
	  {
	    text = _message[i].substr(_message[i].find(',') + 1);
	    m_splitter.clear();
	    m_splitter.split(text, " ");
	    m_splitter.moveTokensTo(vecInfo);
	    if (vecInfo.size() >= 3)
	      {
		if (std::stoul(vecInfo[0]) == m_trackId &&
		    std::stoul(vecInfo[1]) == m_curLvl && vecInfo[2] == "HELP")
		  {
		    m_dir = static_cast<std::size_t>(
		        std::stoi(_message[i].substr(8, 1)));
		    _message.clear();
		    return true;
		  }
	      }
	  }
      }
    return false;
  }

  bool AILogic::finalForwardJoin()
  {
    Logger::log(Logger::_DEBUG_, "[AI] doing last forward");
    sendActionAndCheckResponse(ACTION::FORWARD, "", 1, {});
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
	    m_splitter.split(text, " ");
	    m_splitter.moveTokensTo(vecInfo);
	    if (vecInfo.size() >= 3)
	      {
		if (std::stoul(vecInfo[0]) == m_trackId &&
		    std::stoul(vecInfo[1]) == m_curLvl && vecInfo[2] == "STOP")
		  {
		    Logger::log(Logger::_DEBUG_,
		                "[AI] Received STOP, moving on");
		    return true;
		  }
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
    // Check if arrived
    if (m_dir == 0)
      {
	Logger::log(Logger::_DEBUG_, "[AI] I'm arrived");
	// Switching to passing waiting State
	m_state = STATE::PASSIVE_WAITING;
      }
    else
      {
	Logger::log(Logger::_DEBUG_,
	            "[AI] Moving to " + std::to_string(m_dir) + " direction");
	// Move to a specific position
	sendActionAndCheckResponse(
	    ACTION::RAW, joinCaseMove[m_dir].first,
	    static_cast<std::uint32_t>(joinCaseMove[m_dir].second), {});
      }
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
        &zappy::AILogic::incantFailed, &zappy::AILogic::sendStop));
    passiveVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::broadcastSuccess, &zappy::AILogic::updateLvl));
    passiveVec.push_back(
        std::make_pair<condPtr, actionPtr>(&zappy::AILogic::broadcastStopPass,
                                           &zappy::AILogic::passiveToInitial));
    passiveVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::checkContent, &zappy::AILogic::pickUpObject));
    m_logic[STATE::PASSIVE_WAITING] = passiveVec;
  }

  bool AILogic::incantFailed()
  {
    bool ko = false;
    if (m_incant)
      {
	// Searching an eventual ko from the server
	for (std::string const &str : _message)
	  {
	    if (str == "ko")
	      {
		ko = true;
	      };
	  }
	if (ko)
	  m_incant = false;
      }
    return ko;
  }

  bool AILogic::sendStop()
  {
    Logger::log(Logger::_DEBUG_,
                "[AI] Incantation failed, I need to broadcast STOP");
    sendActionAndCheckResponse(ACTION::BROADCAST,
                               std::to_string(m_id) + " " +
                                   std::to_string(m_curLvl) + " STOP",
                               1, {});
    _message.clear();
    m_state = STATE::INITIAL;
    return false;
  }

  bool AILogic::broadcastSuccess()
  {
    bool levelUp = false;

    // Searching for a Current lvl up in the messages
    for (std::string const &str : _message)
      {
	if (str.substr(0, str.find(":")) == "Current level")
	  {
	    std::uint64_t lvl =
	        std::stoul(str.substr(str.find(": ") + 1, str.length()));
	    if (lvl > this->m_curLvl)
	      levelUp = true;
	  }
      }
    return levelUp;
  }

  bool AILogic::updateLvl()
  {
    ++m_curLvl;
    Logger::log(Logger::_DEBUG_,
                "[AI] Incantation succeeded, current level : " +
                    std::to_string(m_curLvl));
    if (m_incant)
      m_incant = false;
    m_state = STATE::INITIAL;
    m_trackId = 0;
    return true;
  }

  bool AILogic::passiveToInitial()
  {
    Logger::log(Logger::_DEBUG_, "[AI] Received STOP broadcast, moving on");
    m_trackId = 0;
    m_state = STATE::INITIAL;
    return true;
  }

  bool AILogic::turnPass()
  {
    if (!m_incant)
      {
	Logger::log(Logger::_DEBUG_, "[AI] Just turning around");
	sendActionAndCheckResponse(ACTION::LEFT, "", 1, {});
      }
    else
      {
	Logger::log(Logger::_DEBUG_, "[AI] Sleeping a bit");
	::usleep(100);
      }
    return true;
  }

  static const std::vector<std::vector<std::uint32_t>> gl_incantations = {
      {1, 1, 0, 0, 0, 0, 0}, {2, 1, 1, 1, 0, 0, 0}, {2, 2, 0, 1, 0, 2, 0},
      {4, 1, 1, 2, 0, 1, 0}, {4, 1, 2, 1, 3, 0, 0}, {6, 1, 2, 3, 0, 1, 0},
      {6, 2, 2, 2, 2, 2, 1}};

  static const std::vector<std::string> gl_names = {
      "player",   "linemate", "deraumere", "sibur",
      "mendiane", "phiras",   "thystame"};

  static std::vector<std::uint32_t> gl_contentDiff;

  bool AILogic::checkContent()
  {
    if (!m_incant)
      {
	Logger::log(Logger::_DEBUG_, "[AI] checking cell content");
	sendActionAndCheckResponse(ACTION::LOOK, "", 1, {});

	if (!_response.empty())
	  {
	    // Getting content off cell 0
	    m_splitter.clear();
	    m_splitter.split(_response[0], "[,]");
	    std::vector<std::string> cells;
	    m_splitter.moveTokensTo(cells);

	    if (!cells.empty())
	      {
		// Splitting cell 0 to a vector of object names
		m_splitter.clear();
		m_splitter.split(cells[0], " ");
		std::vector<std::string> objects;
		m_splitter.moveTokensTo(objects);

		if (objects.size() >= 7)
		  {
		    // Counting objects
		    gl_contentDiff.clear();
		    gl_contentDiff.resize(7, 0);
		    for (std::string const &obj : objects)
		      {
			for (std::uint32_t i = 0; i < gl_names.size(); ++i)
			  {
			    if (gl_names[i] == obj)
			      {
				++gl_contentDiff[i];
				break;
			      }
			  }
		      }

		    // Ignoring "player" difference
		    gl_contentDiff[0] = gl_incantations[m_curLvl - 1][0];

		    // Return difference between required and actual content
		    return gl_contentDiff != gl_incantations[m_curLvl - 1];
		  }
	      }
	  }
      }
    return false;
  }

  bool AILogic::pickUpObject()
  {
    std::uint32_t count = 0;
    std::string   cmd = "";

    Logger::log(Logger::_DEBUG_, "[AI] I need to adjust the cell");
    // Building take request
    for (std::uint32_t i = 1; i < gl_contentDiff.size() && count < 10; ++i)
      {
	while (gl_contentDiff[i] > gl_incantations[m_curLvl - 1][i] &&
	       count < 10)
	  {
	    if (count)
	      cmd += "\n";
	    cmd += "Take " + gl_names[i];
	    ++count;
	    --gl_contentDiff[i];
	  }
      }

    if (count)
      sendActionAndCheckResponse(ACTION::RAW, cmd, count, {});

    return true;
  }

  bool AILogic::broadcastStopPass()
  {
    bool stop = false;

    for (std::string const &str : _message)
      {
	if (str.find("message ") != std::string::npos)
	  {
	    m_splitter.clear();
	    m_splitter.split(str, ",");
	    std::vector<std::string> prefix;
	    m_splitter.moveTokensTo(prefix);

	    if (!prefix.empty())
	      {
		int dir = std::stoi(prefix[0].substr(prefix[0].find(" ")));

		m_splitter.clear();
		m_splitter.split(prefix[1], " ");
		std::vector<std::string> message;
		m_splitter.moveTokensTo(message);

		if (message.size() >= 3)
		  {
		    if (!dir && std::stoul(message[0]) == m_trackId &&
		        std::stoul(message[1]) == m_curLvl &&
		        message[2] == "STOP")
		      {
			stop = true;
		      }
		  }
	      }
	  }
      }
    return stop;
  }

  /*
   *  Fill vector of methods Active State
   */
  void AILogic::fillActiveState()
  {
    std::vector<std::pair<condPtr, actionPtr>> activeVec;

    activeVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::missingPlayer, &zappy::AILogic::broadcastHelpActive));
    activeVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::adjustResources, &zappy::AILogic::incantation));
    m_logic[STATE::ACTIVE_WAITING] = activeVec;
  }

  /*
   * Check nb Player on the current case
   */
  bool AILogic::missingPlayer()
  {
    std::size_t nbPlayer{0};
    std::size_t countNbPlayer{0};

    look();
    // Check the nb of player depends of the current lvl
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
    if (!m_look.empty())
      {
	m_splitter.clear();
	m_splitter.split(m_look[0], " ", false);
	std::vector<std::string> curCase;
	m_splitter.moveTokensTo(curCase);
	for (std::string inCase : curCase)
	  {
	    if (inCase == "player")
	      ++countNbPlayer;
	  }
	return nbPlayer > countNbPlayer;
      }
    return true;
  }

  /*
   *  Ask help of other AI, and begin to adjust nb obj on the current case
   */
  bool AILogic::broadcastHelpActive()
  {
    static bool shouldBroadCast(true);

    if (shouldBroadCast)
      {
        Logger::log(Logger::_DEBUG_,
                    "[AI] Missing some players, calling help");
        sendActionAndCheckResponse(ACTION::BROADCAST,
                                   std::to_string(m_id) + " " +
                                   std::to_string(m_curLvl) + " HELP",
                                   1, {});
      }
    else
      {
        Logger::log(Logger::_DEBUG_,
                    "[AI] Missing some players, waiting them");
        sendActionAndCheckResponse(ACTION::LEFT, "", 1, {});
      }
    shouldBroadCast = !shouldBroadCast;

    m_playerStayedFor = 0;
    adjustResources();
    return true;
  }

  /*
   * Adjust the number element in the case to begin incantation
   */
  bool AILogic::adjustResources()
  {
    static bool shouldBroadCast(true);
    // Players stayed for x turn
    ++m_playerStayedFor;
    if (m_playerStayedFor < 3 && m_curLvl > 1)
      {
	if (shouldBroadCast)
	  {
	    Logger::log(Logger::_DEBUG_,
	                "[AI] Missing some players, calling help");
	    sendActionAndCheckResponse(ACTION::BROADCAST,
	                               std::to_string(m_id) + " " +
	                                   std::to_string(m_curLvl) + " HELP",
	                               1, {});
	  }
	else
	  {
	    Logger::log(Logger::_DEBUG_,
	                "[AI] Missing some players, waiting them");
	    sendActionAndCheckResponse(ACTION::LEFT, "", 1, {});
	  }
	shouldBroadCast = !shouldBroadCast;
      }

    // Compare resource of the current case and what it needs for the
    // incantation
    std::vector<std::uint32_t> nbObjInCase;
    nbObjInCase.resize(7, 0);

    nbObjInCase[0] = gl_incantations[m_curLvl - 1][0];
    std::vector<std::string> typeObjInCase;

    if (!m_look.empty())
      {
	m_splitter.clear();
	m_splitter.split(m_look[0], " ", false);
	m_splitter.moveTokensTo(typeObjInCase);

	// Loop on all obj in the case
	for (std::string typeObj : typeObjInCase)
	  {
	    std::uint32_t idxType(0);
	    for (std::string type : gl_names)
	      {
		if (type != "player" && type == typeObj)
		  {
		    ++nbObjInCase[idxType];
		    break;
		  }
		++idxType;
	      }
	  }

	if (nbObjInCase == gl_incantations[m_curLvl - 1])
	  {
	    // Object on case correspond to incantation requirement
	    return m_playerStayedFor > 2;
	  }
	else
	  {
	    Logger::log(Logger::_DEBUG_, "[AI] Adusting cell content");
	    // Miss or too much obj in the current case. Send a specific
	    // command
	    // which adjust nb of obj.
	    std::string   needed("");
	    std::uint32_t nbCommand(0);
	    for (std::uint32_t idx(0); idx < nbObjInCase.size(); ++idx)
	      {
		if (nbObjInCase[idx] > gl_incantations[m_curLvl - 1][idx])
		  {
		    if (needed != "")
		      needed += "\n";
		    needed += "Take " + gl_names[idx];
		    ++nbCommand;
		  }
		else if (nbObjInCase[idx] < gl_incantations[m_curLvl - 1][idx])
		  {
		    if (needed != "")
		      needed += "\n";
		    needed += "Set " + gl_names[idx];
		    ++nbCommand;
		  }
	      }
	    if (nbCommand)
	      {
		sendActionAndCheckResponse(ACTION::RAW, needed, nbCommand, {});
	      }
	    return false;
	  }
      }
    return false;
  }

  bool AILogic::incantation()
  {
    Logger::log(Logger::_DEBUG_, "[AI] Starting INCANTATION");
    m_startedIncantation = true;
    if (sendActionAndCheckResponse(ACTION::INCANTATION, "", 1,
                                   {"Elevation underway"}))
      {
	m_incant = true;
	m_state = STATE::PASSIVE_WAITING;
      }
    else
      {
	m_state = STATE::INITIAL;
	sendActionAndCheckResponse(ACTION::BROADCAST,
	                           std::to_string(m_id) + " " +
	                               std::to_string(m_curLvl) + " STOP",
	                           1, {});
      }
    m_startedIncantation = false;
    m_playerStayedFor = 0;
    return true;
  }

  bool AILogic::wasWaiting()
  {
    return m_state == STATE::ACTIVE_WAITING;
  }

  bool AILogic::stopBroadcast()
  {
    sendActionAndCheckResponse(ACTION::BROADCAST,
                               std::to_string(m_id) + " " +
                                   std::to_string(m_curLvl) + " STOP",
                               1, {});
    return true;
  }

  void AILogic::fillInitialState()
  {
    std::vector<std::pair<condPtr, actionPtr>> initialVec;

    initialVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::needFood, &zappy::AILogic::searchFood));
    initialVec.push_back(
        std::make_pair<condPtr, actionPtr>(&zappy::AILogic::wasOnWaitingState,
                                           &zappy::AILogic::goToWaitingState));
    initialVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::wasOnJoinningState,
        &zappy::AILogic::goToJoinningState));
    initialVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::receivedHelp, &zappy::AILogic::initJoinningState));
    initialVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::wasOnSearchingState,
        &zappy::AILogic::goToSearchingState));
    initialVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::canIFork, &zappy::AILogic::goFork));
    initialVec.push_back(std::make_pair<condPtr, actionPtr>(
        &zappy::AILogic::missingObject, &zappy::AILogic::searchObject));
    m_logic[STATE::INITIAL] = initialVec;
  }

  bool AILogic::needFood()
  {
    sendActionAndCheckResponse(ACTION::INVENTORY, "", 1, {});
    inventory_t inventory = getInventory(_response[0]);
    if (inventory.size())
      {
	if (inventory[OBJECTS::FOOD] < 4)
	  m_needFood = true;
	else if (inventory[OBJECTS::FOOD] > 15 + 3 * m_curLvl - 1)
	  m_needFood = false;
	return (m_needFood);
      }
    return (true);
  }

  bool AILogic::searchFood()
  {
    Logger::log(Logger::_DEBUG_, "[AI] I need food");
    if (wasWaiting())
      {
	stopBroadcast();
	_message.clear();
      }
    m_search.clear();
    m_search.push_back(std::make_pair<std::string, bool>("food", false));
    m_state = SEARCHING;
    return true;
  }

  bool AILogic::wasOnWaitingState()
  {
    return m_state == STATE::PASSIVE_WAITING ||
           m_state == STATE::ACTIVE_WAITING;
  }

  bool AILogic::goToWaitingState()
  {
    if (m_state == STATE::PASSIVE_WAITING)
      Logger::log(Logger::_DEBUG_, "[CONDITION] WAS ON PASSIVE STATE");
    else
      Logger::log(Logger::_DEBUG_, "[CONDITION] WAS ON ACTIVE STATE");
    return true;
  }

  bool AILogic::wasOnJoinningState()
  {
    return m_state == STATE::JOINING;
  }

  bool AILogic::goToJoinningState()
  {
    Logger::log(Logger::_DEBUG_, "[CONDITION] WAS ON JOINING STATE");
    return true;
  }

  bool AILogic::receivedHelp()
  {
    std::vector<std::string> vecInfo;
    std::string              text;

    for (std::string msg : _message)
      {
	if (msg.substr(0, 7) == "message")
	  {
	    text = msg.substr(msg.find(',') + 1);
	    m_splitter.clear();
	    m_splitter.split(text, " ");
	    m_splitter.moveTokensTo(vecInfo);
	    if (vecInfo.size() >= 3)
	      {
		std::size_t curId = std::stoul(vecInfo[0]);
		if (curId != m_id && std::stoul(vecInfo[1]) == m_curLvl &&
		    vecInfo[2] == "HELP")
		  {
		    m_dir =
		        static_cast<std::size_t>(std::stoi(msg.substr(8, 1)));
		    m_trackId = curId;
		    return true;
		  }
	      }
	  }
      }
    return false;
  }

  bool AILogic::initJoinningState()
  {
    Logger::log(Logger::_DEBUG_, "[CONDITION] HELP ASKED");
    m_timeout = std::rand() % 4 + 2;
    m_state = STATE::JOINING;
    return false;
  }

  bool AILogic::wasOnSearchingState()
  {
    return m_state == STATE::SEARCHING;
  }

  bool AILogic::goToSearchingState()
  {
    Logger::log(Logger::_DEBUG_, "[CONDITION] WAS ON SEARCHING STATE");
    return true;
  }

  bool AILogic::canIFork()
  {
    static uint32_t cooldown = 0;

    if (cooldown == 0)
      {
        sendActionAndCheckResponse(ACTION::UNUSED_SLOTS, "", 1, {});
        if (_response.empty())
          return false;
        if (!std::stoi(_response[0]))
          {
            cooldown = 650;
            return (true);
          }
        return (false);
      }
    else
      {
        --cooldown;
      }
    return (false);
  }

  bool AILogic::goFork()
  {
    Logger::log(Logger::_DEBUG_, "[AI] I can lay an egg");
    sendActionAndCheckResponse(ACTION::FORK, "", 1, {});
    sendActionAndCheckResponse(ACTION::FORWARD, "", 1, {});
    return true;
  }

  bool AILogic::missingObject()
  {
    sendActionAndCheckResponse(ACTION::INVENTORY, "", 1, {});
    if (!_response.empty())
      {
	inventory_t inventory = getInventory(_response[0]);
	m_search.clear();
	if (!inventory.empty())
	  {
	    for (std::size_t idx(1);
	         idx < gl_incantations[m_curLvl - 1].size(); ++idx)
	      {
		if (inventory[idx] < gl_incantations[m_curLvl - 1][idx])
		  {
		    m_search.push_back(std::make_pair<std::string, bool>(
		        std::string(gl_names[idx]), false));
		    return true;
		  }
	      }
	    return false;
	  }
      }
    m_search.push_back(std::make_pair<std::string, bool>("food", false));
    return true;
  }

  bool AILogic::searchObject()
  {
    Logger::log(Logger::_DEBUG_, "[AI] Missing some object to level up");
    m_state = STATE::SEARCHING;
    return true;
  }

  bool AILogic::isIncantating() const
  {
    return m_incant;
  }

  bool AILogic::startedImcatation() const
  {
    return m_startedIncantation;
  }
}
