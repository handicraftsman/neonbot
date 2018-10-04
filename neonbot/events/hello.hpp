#pragma once

#include <memory>

#include "../event.hpp"

namespace NB {

  class EventHello;
  using EventHelloPtr = std::shared_ptr<EventHello>;

  class EventHello : public Event {
  public:
    EventHello();
    virtual ~EventHello();
  };
  
}