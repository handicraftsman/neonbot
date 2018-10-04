#pragma once

#include <memory>

#include <guosh.hpp>

namespace NB {
  class Plugin;
  using PluginPtr = std::shared_ptr<Plugin>;
}

namespace NB {

  class Plugin {
  public:
    Plugin(const std::string& name, const std::string& sopath);
    ~Plugin();

  private:
    Guosh::Logger log;
    std::string name;
    std::string sopath;
    std::shared_ptr<void> handle;
  };
  
}