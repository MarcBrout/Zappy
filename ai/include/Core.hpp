//
// Created by Pierre Bougon on 21/06/17.
//

#ifndef CLIENTAI_CORE_HPP_
#define CLIENTAI_CORE_HPP_

#include "ai_logic/AILogic.hpp"

namespace zappy
{
  class Core
  {
  public:
    Core();
    Core(Core const &other) = delete;
    ~Core();

    Core &operator=(Core const &other) = delete;

    void run();
    void auth(std::string teamName);
    bool waitForReponses(std::int32_t                    count,
                         std::vector<std::string> const &anwsers);

  private:
    bool         _running;
    std::int32_t _waitingForResponse;
    AILogic      _ai;

    void manageResponse(std::string servMessage);
  };
}

#endif // !CLIENTAI_CORE_HPP_
