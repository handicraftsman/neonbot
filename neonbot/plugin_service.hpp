#pragma once

#include <map>
#include <memory>
#include <vector>

#include <particledi.hpp>

namespace NB {
  class PluginService;
  using PluginServicePtr = std::shared_ptr<PluginService>;
}

#include "plugin.hpp"

namespace NB {

  class PluginService : public particledi::dependency {
  public:
    PluginService(std::weak_ptr<particledi::dm> dm);
    virtual ~PluginService();

    void connect_to_event_service();

    void add_path(const std::string& path);
    void load(const std::string& name);

  private:
    std::weak_ptr<particledi::dm> dm;
    std::vector<std::string> paths;
    std::map<std::string, PluginPtr> plugins;
  };
  
}