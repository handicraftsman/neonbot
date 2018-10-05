#include "bot.hpp"

#include "config_service.hpp"
#include "event_service.hpp"
#include "plugin_service.hpp"
#include "redis_service.hpp"

#include "events.hpp"

#include <regex>

#include <particletk/create.hpp>

#include <guosh.hpp>

/*
 * Private declaration
 */

namespace NB {

  class BotPriv {
  public:
    BotPriv(Bot* pub, std::weak_ptr<particledi::dm> dm);
    ~BotPriv();

    void load_config();
    void start();

    Bot* pub;
    std::weak_ptr<particledi::dm> dm;
    Guosh::Logger log;
    std::shared_ptr<Config> cfg;
    EventHandlerMapPtr ehm;
  };
  
}

/*
 * Private implementation
 */

NB::BotPriv::BotPriv(Bot* pub, std::weak_ptr<particledi::dm> dm)
: pub(pub)
, dm(dm)
, log("bot")
, ehm(new NB::EventHandlerMap())
{
  dm.lock()->get<NB::PluginService>()->connect_to_event_service();

  ehm->set<NB::EventHello>([this] (NB::EventHelloPtr e) {
    log("Hello, World!");
  });
  
  auto es = dm.lock()->get<NB::EventService>();

  es->subscribe([this] (NB::EventPtr e) {
    ehm->handle(e);
  });
  
  es->emit(PTK::create<NB::EventHello>());
}

NB::BotPriv::~BotPriv() {}

void NB::BotPriv::load_config() {
  if (cfg) return;
  log.debug("Poking the config service to get us a config");
  cfg = dm.lock()->get<NB::ConfigService>()->get_config();

  std::regex addr_rgx("(.+):(\\d{1,5})");
  std::smatch m {};

  if (std::regex_match(cfg->redis->addr, m, addr_rgx)) {
    std::string host;
    uint16_t port;
    host = m[1];
    port = std::stoi(m[2]);
    auto rs = dm.lock()->get<NB::RedisService>();
    log.debug("Poking the redis service to connect to the redis server (lol)");
    rs->connect(host, port, cfg->redis->pass);
  } else {
    throw std::runtime_error("invalid redis address");
  }

}

void NB::BotPriv::start() {
  log.debug("Poking the connection service to establish a connection to the Discord API");
}

/*
 * Public implementation
 */

NB::Bot::Bot(std::weak_ptr<particledi::dm> dm) {
  priv = new NB::BotPriv(this, dm);
  dm.lock()->set<NB::Bot>(this);
}

NB::Bot::~Bot() {
  delete priv;
}

void NB::Bot::load_config() {
  priv->load_config();
}

void NB::Bot::start() {
  priv->start();
}