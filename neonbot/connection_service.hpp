#pragma once

#include <memory>

#include <particledi.hpp>

namespace NB {
  class ConnectionService;
  using ConnectionServicePtr = std::shared_ptr<ConnectionService>;
  class ConnectionServicePriv;
}

namespace NB {

  class ConnectionService : public particledi::dependency {
  public:
    ConnectionService(std::weak_ptr<particledi::dm> dm);
    virtual ~ConnectionService();

    void set_token(const std::string& tkn);

    ConnectionServicePriv* priv;
  };
  
}