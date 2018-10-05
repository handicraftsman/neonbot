#pragma once

#include <memory>

#include <guosh.hpp>

namespace NB {
  class Plugin;
  using PluginPtr = std::shared_ptr<Plugin>;
}

#include "event.hpp"

namespace NB {

  class Plugin {
  public:
    Plugin(const std::string& name, const std::string& sopath);
    ~Plugin();
    void handle_event(EventPtr e);

  private:
    Guosh::Logger log;
    std::string name;
    std::string sopath;
    std::shared_ptr<void> handle;
    EventHandlerMapPtr ehm;
  };
  
}

extern "C" {
  void nb_init(std::string name);
  void nb_deinit();
}