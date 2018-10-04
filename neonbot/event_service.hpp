#pragma once

#include <memory>
#include <vector>

#include <particledi.hpp>

namespace NB {
  class EventService;
  using EventServicePtr = std::shared_ptr<EventService>;
}

#include "event.hpp"

namespace NB {

  class EventService : public particledi::dependency {
  public:
    EventService();
    virtual ~EventService();

    void emit(EventPtr e);
    void subscribe(EventHandler h);

  private:
    std::vector<EventHandler> handlers;
  };
  
}