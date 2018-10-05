#include <particlepm.hpp>

using namespace PPM::Utils;

PPM_PACKAGE(p) {
  p->name("neonbot");
  p->version(PPM::Version("v0.1.0"));
  p->description("A Discord bot framework");
  p->github(PPM::GitHub("handicraftsman", "neonbot"));
  p->license(PPM::License("MIT", "https://github.com/handicraftsman/neonbot/blob/master/LICENSE.txt"));

  PPM::libs.insert("boost_system");
  PPM::libs.insert("hiredis");
  PPM::libs.insert("jsoncpp");

  PPM::GitHubPtr
    pdi_d    = p->github_repo("handicraftsman", "particledi"),
    guosh_d  = p->github_repo("handicraftsman", "guosh"),
    box_d    = p->github_repo("particletk",     "box"),
    create_d = p->github_repo("particletk",     "create");
  std::string
    hiredis_f = p->pkgconfig("hiredis"),
    jsoncpp_f = p->pkgconfig("jsoncpp");

  std::vector<std::string> lib_src {
    "neonbot/bot.cpp",
    "neonbot/event.cpp",
    "neonbot/plugin.cpp",

    "neonbot/boost_ios_service.cpp",
    "neonbot/config_service.cpp",
    "neonbot/connection_service.cpp",
    "neonbot/event_service.cpp",
    "neonbot/plugin_service.cpp",
    "neonbot/redis_service.cpp",

    "neonbot/events/hello.cpp"
  };

  std::string flags = flagcat({
    ("-L" + PPM::dist_dir),

    "-lboost_system",

    "-lparticledi",
    "-lguosh",

    "-ldl",
    "-lpthread",

    ("-I" + p->pkg_dir()),
    ("-I" + pdi_d->dir()),
    ("-I" + guosh_d->dir() + "/src"),
    ("-I" + box_d->dir()),
    ("-I" + create_d->dir()),

    hiredis_f,
    jsoncpp_f
  });

  PPM::TargetPtr lib = p->library("libneonbot");
  lib->name("neonbot");
  lib->cpp("gnu++17");
  lib->cpp_files(lib_src);
  lib->cpp_flags(flags);

  PPM::TargetPtr core_p = p->library("nb-core");
  core_p->cpp("gnu++17");
  core_p->cpp_files(std::vector<std::string> {
    "plugins/core.cpp"
  });
  core_p->cpp_flags(flags);
  core_p->cpp_flags("-lneonbot");
  core_p->depends(lib);

  PPM::TargetPtr exe = p->executable("neonbot");
  exe->cpp("gnu++17");
  exe->cpp_files(std::vector<std::string> {
    "main.cpp"
  });
  exe->cpp_flags(flags);
  exe->cpp_flags("-lneonbot");
  exe->depends(lib);
}
