#include "core/paths.h"
#include "core/atomic_write.h"
#include <cassert>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void test_atomic_write_permission() {
    fs::remove_all("tmp_core_perm");
    Persist::Config cfg; cfg.baseDir = "tmp_core_perm"; Persist::setConfig(cfg);
    fs::path p = Persist::dataPath("perm.json");
    Persist::atomicWrite(p, "{\"a\":1}");
    Persist::atomicWrite(p, "{\"a\":1}"); // cria backup
    fs::permissions(p, fs::perms::owner_write, fs::perm_options::remove);
    bool ok = Persist::atomicWrite(p, "{\"a\":2}");
    assert(!ok);
    std::ifstream f(p);
    std::string content; std::getline(f, content);
    assert(content.find("1") != std::string::npos);
    fs::permissions(p, fs::perms::owner_write, fs::perm_options::add);
    fs::remove_all("tmp_core_perm");
}

void test_restore_backup() {
    fs::remove_all("tmp_core_restore");
    Persist::Config cfg; cfg.baseDir = "tmp_core_restore"; Persist::setConfig(cfg);
    fs::path p = Persist::dataPath("restore.json");
    Persist::atomicWrite(p, "orig");
    Persist::atomicWrite(p, "orig"); // cria backup
    {
        std::ofstream f(p, std::ios::trunc); f << "corrupt";
    }
    bool restored = Persist::restoreBackup(p);
    assert(restored);
    std::ifstream f(p);
    std::string s; std::getline(f, s);
    assert(s == "orig");
    fs::remove_all("tmp_core_restore");
}
