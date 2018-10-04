#include "connection_service.hpp"

#include <optional>

/*
 * Private declaration
 */

namespace NB {

  class ConnectionServicePriv {
  public:
    ConnectionServicePriv(ConnectionService* pub, std::weak_ptr<particledi::dm> dm);
    ~ConnectionServicePriv();

    ConnectionService* pub;
    std::weak_ptr<particledi::dm> dm;
    std::optional<std::string> token;    
  };
  
}

/*
 * Private implementation
 */

NB::ConnectionServicePriv::ConnectionServicePriv(ConnectionService* pub, std::weak_ptr<particledi::dm> dm)
: pub(pub)
, dm(dm)
{}

NB::ConnectionServicePriv::~ConnectionServicePriv() {}

/*
 * Public implementation
 */

NB::ConnectionService::ConnectionService(std::weak_ptr<particledi::dm> dm) {
  priv = new ConnectionServicePriv(this, dm);
}

NB::ConnectionService::~ConnectionService() {
  delete priv;
}

void NB::ConnectionService::set_token(const std::string& tkn) {
  priv->token = tkn;
}