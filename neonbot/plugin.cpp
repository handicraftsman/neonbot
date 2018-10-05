#include "plugin.hpp"

#include <dlfcn.h>

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