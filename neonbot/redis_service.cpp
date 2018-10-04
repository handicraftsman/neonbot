#include "redis_service.hpp"

#include <iostream>

#include <cstdlib>

NB::RedisService::RedisService(std::weak_ptr<particledi::dm> dm)
: log("redis")
{
  redisPtr_ = nullptr;
}

NB::RedisService::~RedisService() {
  if (redisPtr_) delete redisPtr_;
}

void NB::RedisService::connect(const std::string& host, uint16_t port, std::optional<std::string> pass) {
  if (redisPtr_) return;

  redisContext* cptr = redisConnect(host.c_str(), port);
  if (cptr == nullptr || cptr->err) {
    if (cptr) {
      log.critical("%s", cptr->errstr);
    } else {
      log.critical("Unable to allocate redis connect");
    }
    std::exit(1);
  }
  
  std::shared_ptr<redisContext> ptr(cptr, redisFree);

  log("Connected to redis");

  redisPtr_ = new PTK::Box<redisContext>(ptr);

  NB::RedisService::RedisAccessor f = [this, pass] (redisContext* ctx) {
    if (pass) {
      redisReply* rpl = static_cast<redisReply*>(redisCommand(ctx, "AUTH %s", pass.value().c_str()));
      if (rpl->type == REDIS_REPLY_ERROR) {
        log.critical("Unable to authenticate into redis");
        std::exit(1);
      }
      freeReplyObject(rpl);
    }
    log("Authenticated into redis");
  };

  redisPtr_->use(f);
}

PTK::Box<redisContext> NB::RedisService::redis() {
  return *redisPtr_;
}