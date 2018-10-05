#pragma once

#include <memory>
#include <thread>
#include <vector>

#include <particledi.hpp>

#include <boost/asio.hpp>

namespace NB {
  class BoostIosService;
  using BoostIosServicePtr = std::shared_ptr<BoostIosService>;
}

namespace NB {

  class BoostIosService : public particledi::dependency {
  public:
    using IosPtr = std::shared_ptr<boost::asio::io_service>;
    using WorkPtr = std::shared_ptr<boost::asio::io_service::work>;
  
    BoostIosService();
    virtual ~BoostIosService();

    IosPtr get_ios();
    void stop();
    void join();

  private:
    IosPtr ios;
    WorkPtr work;
    std::vector<std::shared_ptr<std::thread>> threads;
  };
  
}