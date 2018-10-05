#include "request_service.hpp"

NB::RequestService::RequestService(std::weak_ptr<particledi::dm> dm)
: dm(dm)
{}

NB::RequestService::~RequestService() {}

NB::RequestService& NB::operator<<(NB::RequestService& reqs, NB::RequestPtr req) {
  req->do_it(req, reqs.dm);
}