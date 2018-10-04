#include "event_service.hpp"

NB::EventService::EventService() {}
NB::EventService::~EventService() {}

void NB::EventService::emit(NB::EventPtr e) {
  for (NB::EventHandler h : handlers) {
    h(e);
  }
}

void NB::EventService::subscribe(NB::EventHandler h) {
  handlers.push_back(h);
}