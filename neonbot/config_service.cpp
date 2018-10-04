#include "config_service.hpp"

#include <fstream>

#include <json/json.h>

NB::ConfigService::ConfigService(const std::string& config_path)
: config_path(config_path)
{}

NB::ConfigService::~ConfigService() {}

std::shared_ptr<NB::Config> NB::ConfigService::get_config() {
  std::shared_ptr<NB::Config> ptr(new NB::Config());
  ptr->redis = std::shared_ptr<NB::ConfigRedis>(new NB::ConfigRedis());

  std::ifstream f(config_path);

  Json::Value root;
  f >> root;

  ptr->token = root["token"].asString();
  ptr->redis->addr = root["redis"]["addr"].asString();
  if (!root["redis"]["pass"].isNull()) {
    ptr->redis->pass = root["redis"]["pass"].asString();
  }

  f.close();

  return ptr;
}