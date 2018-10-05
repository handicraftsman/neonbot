#pragma once

#include <memory>

#include <particledi.hpp>

namespace NB {
  class Request;
  using RequestPtr = std::shared_ptr<Request>;
}

namespace NB {

  class Request {
  public:
    Request();
    virtual ~Request();
    virtual void do_it(RequestPtr _r, std::weak_ptr<particledi::dm> dm) = 0;
  };

}