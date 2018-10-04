#pragma once

#include <memory>

#include <particledi.hpp>

namespace NB {
  class ConfigService;
  using ConfigServicePtr = std::shared_ptr<ConfigService>;
}

#include "config.hpp"

namespace NB {

  class ConfigService : public particledi::dependency {
  public:
    ConfigService(const std::string& config_path);
    virtual ~ConfigService();

    std::shared_ptr<Config> get_config();

  private:
    std::string config_path;
  };
  
}