//
// Created by brout_m on 26/06/17.
//

#include "ai_logic/AILogic.hpp"

namespace zappy
{
  AILogic::~AILogic()
  {
  }

  AILogic::AILogic() : CoreAI(), m_state(AILogic::STATE::NONE)
  {
  }

}