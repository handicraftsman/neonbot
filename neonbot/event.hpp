#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <typeinfo>
#include <typeindex>

namespace NB {
  class Event;
  using EventPtr = std::shared_ptr<Event>;
  using EventHandler = std::function<void(EventPtr)>;
  class EventHandlerMap;
  using EventHandlerMapPtr = std::shared_ptr<EventHandlerMap>;
}

namespace NB {

  class Event {
  public:
    Event();
    virtual ~Event();
  };

  class EventHandlerMap {
  private:
    mutable std::map<std::type_index, EventHandler> handlers;

  public:
    #define WRAPPER(h)                                    \
      [h] (EventPtr e) {                                  \
        auto ce = std::dynamic_pointer_cast<T>(e);        \
        if (ce) {                                         \
          h(ce);                                          \
        } else {                                          \
          std::cerr << "Invalid event case" << std::endl; \
        }                                                 \
      }                                                   \

    template<typename T, typename H>
    void set(H h) {
      handlers[std::type_index(typeid(T))] = WRAPPER(h);
    }

    #undef WRAPPER

    template<typename T>
    EventHandler get() const {
      return handlers[std::type_index(typeid(T))];
    }

    inline EventHandler get(std::type_index t) const {
      return handlers[t];
    }

    inline void handle(EventPtr e) const {
      #define Q std::type_index(typeid(*(e.get())))
      if (handlers.find(Q) != handlers.end()) {
        handlers[Q](e);
      }
      #undef Q
    }

    inline void operator()(EventPtr e) const {
      handle(e);
    }
  };
  
}