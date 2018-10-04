#pragma once

#include <memory>

#include <particledi.hpp>

namespace NB {
  class Bot;
  class BotPriv;
  using BotPtr = std::shared_ptr<Bot>;
}

namespace NB {

  class Bot : public particledi::dependency {
  public:
    Bot(std::weak_ptr<particledi::dm> dm);
    virtual ~Bot();

    void load_config();
    void start();

  private:
    BotPriv* priv;
  };

}
