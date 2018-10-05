#include "boost_ios_service.hpp"

#include <unistd.h>

NB::BoostIosService::BoostIosService() {
  ios.reset(new boost::asio::io_service());
  work.reset(new boost::asio::io_service::work(*ios.get()));
  
  int cores = sysconf(_SC_NPROCESSORS_ONLN);
  for (int i = 0; i < cores; ++i) {
    std::shared_ptr<std::thread> thr(new std::thread([this] () {
      ios->run();
    }));
    threads.push_back(thr);
  }
}

NB::BoostIosService::~BoostIosService() {
  work.reset();
}

NB::BoostIosService::IosPtr NB::BoostIosService::get_ios() {
  return ios;
}

void NB::BoostIosService::stop() {
  work.reset();
}

void NB::BoostIosService::join() {
  for (std::shared_ptr<std::thread> thr : threads) {
    thr->join();
  }
}