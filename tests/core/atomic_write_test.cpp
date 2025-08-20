#include "core/persist.h"
#include <cassert>
#include <filesystem>
#include <fstream>

void test_atomic_write_permission() {
    using namespace std::filesystem;
    remove_all("tmp_core_perm");
    Persist::Config cfg; cfg.baseDir = "tmp_core_perm"; Persist::setConfig(cfg);
    fs::path p = Persist::dataPath("perm.json");
    Persist::atomicWrite(p, "{\"a\":1}");
    Persist::atomicWrite(p, "{\"a\":1}"); // cria backup
    permissions(p, fs::perms::owner_write, fs::perm_options::remove);
    bool ok = Persist::atomicWrite(p, "{\"a\":2}");
    assert(!ok);
    std::ifstream f(p);
    std::string content; std::getline(f, content);
    assert(content.find("1") != std::string::npos);
    permissions(p, fs::perms::owner_write, fs::perm_options::add);
    remove_all("tmp_core_perm");
}

void test_restore_backup() {
    using namespace std::filesystem;
    remove_all("tmp_core_restore");
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
    remove_all("tmp_core_restore");
}
