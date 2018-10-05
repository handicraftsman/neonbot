#pragma once

#include <memory>

#include <particledi.hpp>

namespace NB {
  class RequestService;
  using RequestServicePtr = std::shared_ptr<RequestService>;
}

#include "request.hpp"

namespace NB {

  RequestService& operator<<(RequestService& reqs, RequestPtr req);

  class RequestService : public particledi::dependency {
  public:
    RequestService(std::weak_ptr<particledi::dm> dm);
    virtual ~RequestService();

    friend RequestService& operator<<(RequestService& reqs, RequestPtr req);

  private:
    std::weak_ptr<particledi::dm> dm;
  };
  
}