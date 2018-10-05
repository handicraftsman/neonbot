#include "plugin.hpp"

#include <dlfcn.h>

#include <cxxabi.h>

typedef void (*InitFunc)(std::string name);
typedef void (*DeinitFunc)();

NB::Plugin::Plugin(const std::string& name, const std::string& sopath)
: log("?" + name)
{
  char* error;

  void* h = dlopen(sopath.c_str(), RTLD_NOW);

  error = dlerror();
  if (error != NULL) {
    throw std::runtime_error(std::string(error));
  }
  
  handle = std::shared_ptr<void>(h, dlclose);

  log.debug("Opened myself");

  InitFunc initf = (InitFunc) dlsym(h, "nb_init");
  if (initf != NULL) {
    initf(name);
  }
  log.debug("Initialized myself");

  log("Hello, World!");
}

NB::Plugin::~Plugin() {
  DeinitFunc deinitf = (DeinitFunc) dlsym(handle.get(), "nb_deinit");
  if (deinitf != NULL) {
    deinitf();
  }
  log.debug("Deinitialized myself");
}

void NB::Plugin::handle_event(NB::EventPtr e) {
  if (ehm) {
    try {
      ehm->handle(e);
    } catch (std::exception& exc) {
      char* exc_name = abi::__cxa_demangle(typeid(exc).name(), NULL, NULL, NULL);
      char* e_name = abi::__cxa_demangle(typeid(*e.get()).name(), NULL, NULL, NULL);
      log.error("Exception in %s\n\t%s\n\t%s", e_name, exc_name, exc.what());
    } catch (...) {
      log.error("Caught an unknown error");
    }
  }
}