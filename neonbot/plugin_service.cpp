#include "plugin_service.hpp"

#include "event_service.hpp"

#include <thread>

NB::PluginService::PluginService(std::weak_ptr<particledi::dm> dm)
: dm(dm)
{}

NB::PluginService::~PluginService() {}

void NB::PluginService::connect_to_event_service() {
  auto es = dm.lock()->get<NB::EventService>();

  es->subscribe([this] (NB::EventPtr e) {
    for (auto& p : plugins) {
      std::thread(&NB::Plugin::handle_event, p.second.get(), e);
    }
  });
}