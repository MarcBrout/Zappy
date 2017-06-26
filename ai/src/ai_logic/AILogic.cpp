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
  }

  bool AILogic::needFood()
  {
    sendActionAndCheckResponse(ACTION::INVENTORY, "", 1, {});
    inventory_t inventory = getInventory(_response[0]);
    return (inventory[OBJECTS::FOOD] < 10);
  }

  inventory_t
      AILogic::getInventory(std::string const &inventory)
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
