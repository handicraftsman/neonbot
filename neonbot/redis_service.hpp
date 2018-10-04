#pragma once

#include <functional>
#include <memory>
#include <optional>

#include <cstdint>

#include <particledi.hpp>
#include <particletk/box.hpp>

#include <guosh.hpp>

#include <hiredis.h>

namespace NB {
  class RedisService;
  using RedisServicePtr = std::shared_ptr<RedisService>;
}

namespace NB {

  class RedisService : public particledi::dependency {
  public:
    using RedisAccessor = std::function<void(redisContext*)>;

    RedisService(std::weak_ptr<particledi::dm> dm);
    virtual ~RedisService();

    void connect(const std::string& host, uint16_t port, std::optional<std::string> pass);
    PTK::Box<redisContext> redis();

    PTK::Box<redisContext>* redisPtr_;

    Guosh::Logger log;
  };
  
}