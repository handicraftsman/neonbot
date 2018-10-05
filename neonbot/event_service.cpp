#include "event_service.hpp"

#include <thread>

NB::EventService::EventService() {}
NB::EventService::~EventService() {}

void NB::EventService::emit(NB::EventPtr e) {
  for (NB::EventHandler h : handlers) {
    std::thread(h, e).detach();
  }
}

void NB::EventService::subscribe(NB::EventHandler h) {
  handlers.push_back(h);
}