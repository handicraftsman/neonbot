#include <cstdlib>

#include <algorithm>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

extern "C" {
  #include <getopt.h>
}

#include <guosh.hpp>
#include <particledi.hpp>

#include "neonbot.hpp"

void set_log_level(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  Guosh::LogLevel lvl = Guosh::LogLevel::INFO;
  if (str == "debug") {
    lvl = Guosh::LogLevel::DEBUG;
  } else if (str == "io" || str == "irc") {
    lvl = Guosh::LogLevel::IO;
  } else if (str == "info") {
    lvl = Guosh::LogLevel::INFO;
  } else if (str == "warning") {
    lvl = Guosh::LogLevel::WARNING;
  } else if (str == "error") {
    lvl = Guosh::LogLevel::ERROR;
  } else if (str == "important") {
    lvl = Guosh::LogLevel::IMPORTANT;
  } else if (str == "critical") {
    lvl = Guosh::LogLevel::CRITICAL;
  } else {
    std::clog << "Invalid log level: " << str << std::endl;
    std::exit(2);
  }
  Guosh::Logger::main_level = lvl;
}

void display_usage(char* pname) {
  std::cout << pname << " [OPTIONS]" << std::endl << std::endl;
  std::cout << "Available options: " << std::endl;
  std::cout << "-h        --help                Show this message" << std::endl;
  std::cout << "-p DIR    --plugin-dir    DIR    Adds a plugin directory" << std::endl;
  std::cout << "-c FILE   --config-file   FILE   Config file [./neonbot.json]" << std::endl;
  std::cout << "-l LEVEL  --log-level     LEVEL  Log level [info]" << std::endl;
  std::cout << "Possible log levels: debug, [io | irc], info, warning, error, important, critical" << std::endl;
}

int main(int argc, char** argv) {
  std::setlocale(LC_ALL, "en_US.UTF-8");

  int opt;

  static struct option long_options[] = {
    {"help",          0,                 NULL, 'h'},
    {"plugin-dir",    required_argument, NULL, 'p'},
    {"config-file",   required_argument, NULL, 'c'},
    {"log-level",     required_argument, NULL, 'l'},
  };

  std::string config_file = "./neonbot.json";
  std::vector<std::string> plugin_dirs;
  plugin_dirs.push_back("./");

  while ((opt = getopt_long(argc, argv, "hp:c:l:", long_options, NULL)) != EOF)
    switch(opt) {
    case 'p':
      plugin_dirs.push_back(std::string(optarg));
      break;
    case 'c':
      config_file = std::string(optarg);
      break;
    case 'l':
      set_log_level(std::string(optarg));
      break;
    case 'h':
      display_usage(argv[0]);
      std::exit(2);
    default:
      std::exit(2);
  }

  Guosh::Logger l("main");
  l.debug("Config file: %s", config_file.c_str());
  for (std::string pd : plugin_dirs) {
    l.debug("Plugin dir: %s", pd.c_str());
  }

  particledi::dm_ptr dm = particledi::dm::create();
  dm->set<NB::ConfigService>(new NB::ConfigService(config_file));
  dm->set<NB::EventService>(new NB::EventService());
  dm->set<NB::ConnectionService>(new NB::ConnectionService(dm));
  dm->set<NB::RedisService>(new NB::RedisService(dm));
  //dm->set<pb::plugin_service>(new pb::plugin_service(dm, plugin_dirs));

  NB::Bot* bot = new NB::Bot(dm);

  bot->load_config();
  bot->start();

  return 0;
}
