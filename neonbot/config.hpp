#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace NB {

  struct ConfigRedis {
    std::string addr;
    std::optional<std::string> pass;
  };

  struct Config {
    std::shared_ptr<ConfigRedis> redis;
    std::vector<std::string> plugins;
    std::string token;
    std::string theme;
  };

}
