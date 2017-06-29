//
// Created by Pierre Bougon on 23/06/17.
//

#ifndef CLIENTAI_COREAI_HPP_
#define CLIENTAI_COREAI_HPP_

#include <vector>
#include "Core.hpp"
#include "tools/Vector2.hpp"

namespace zappy
{
  class CoreAI
  {
  public:
    enum ACTION
    {
      FORWARD,
      LEFT,
      RIGHT,
      LOOK,
      INVENTORY,
      BROADCAST,
      UNUSED_SLOTS,
      FORK,
      EJECT,
      TAKE,
      SET,
      INCANTATION,
      RAW
    };

    virtual ~CoreAI(){};
    explicit CoreAI(Core &core);
    void nextAction();
    void sendAction(CoreAI::ACTION, const std::string &str = "");
    bool sendActionAndCheckResponse(CoreAI::ACTION                  action,
                                    const std::string &             str,
                                    std::uint32_t                   count,
                                    const std::vector<std::string> &anws);
    void setMessage(const std::string &string);
    void addResponse(const std::string &string);
    void                            resetResponse();
    std::vector<std::string> const &getResponse();

    void setX(size_t x);
    void setY(size_t y);

  protected:
    Core &                   _core;
    std::vector<std::string> _message;
    std::vector<std::string> _response;
    Vector2s                 _pos;

    typedef void (*_action_t)(const std::string &);
    std::vector<_action_t> _actions;
  };
}

#endif // !CLIENTAI_COREAI_HPP_
