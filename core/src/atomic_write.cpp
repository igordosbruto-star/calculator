#include "core/atomic_write.h"
#include "core/paths.h"
#include <fstream>

namespace Persist {

bool hasWritePermission(const fs::path& p) {
    std::error_code ec;
    fs::perms perms = fs::status(p, ec).permissions();
    if (ec) return false;
    return (perms & fs::perms::owner_write) != fs::perms::none ||
           (perms & fs::perms::group_write) != fs::perms::none ||
           (perms & fs::perms::others_write) != fs::perms::none;
}

bool restoreBackup(const fs::path& finalPath) {
    const fs::path bakPath = finalPath.string() + ".bak";
    std::error_code ec;
    if (!fs::exists(bakPath)) return false;
    fs::copy_file(bakPath, finalPath, fs::copy_options::overwrite_existing, ec);
    if (ec) {
        wr::p("PERSIST", finalPath.string() + " restore fail: " + ec.message(), "Red");
        return false;
    }
    wr::p("PERSIST", finalPath.string() + " restored from backup.", "Yellow");
    return true;
}

bool atomicWrite(const fs::path& finalPath, const std::string& content) {
    try {
        if (!finalPath.parent_path().empty()) {
            std::error_code ecDir;
            bool dirCreated = fs::create_directories(finalPath.parent_path(), ecDir);
            if (ecDir) {
                wr::p("PERSIST", finalPath.parent_path().string() + " create fail: " + ecDir.message(), "Red");
                return false;
            } else if (dirCreated) {
                wr::p("PERSIST", finalPath.parent_path().string() + " criado.", "Green");
            }
        }

        bool existed = fs::exists(finalPath);
        if (existed && !hasWritePermission(finalPath)) {
            wr::p("PERSIST", finalPath.string() + " sem permissao de escrita", "Red");
            return false;
        }
        const fs::path tmpPath = finalPath.string() + ".tmp";
        const fs::path bakPath = finalPath.string() + ".bak";

        {
            std::ofstream f(tmpPath, std::ios::out | std::ios::trunc | std::ios::binary);
            if (!f) {
                wr::p("PERSIST", tmpPath.string() + " open fail", "Red");
                return false;
            }
            f.write(content.data(), static_cast<std::streamsize>(content.size()));
            if (!f) {
                wr::p("PERSIST", tmpPath.string() + " write fail", "Red");
                return false;
            }
        }

        if (existed) {
            std::error_code ec;
            fs::copy_file(finalPath, bakPath, fs::copy_options::overwrite_existing, ec);
            if (ec) {
                wr::p("PERSIST", finalPath.string() + " backup copy fail: " + ec.message(), "Yellow");
            }
        }

        std::error_code ec2;
        fs::rename(tmpPath, finalPath, ec2);
        if (ec2) {
            std::error_code ec3;
            fs::remove(finalPath, ec3);
            fs::rename(tmpPath, finalPath, ec2);
            if (ec2) {
                wr::p("PERSIST", finalPath.string() + " rename fail: " + ec2.message(), "Red");
                std::error_code ec4; fs::remove(tmpPath, ec4);
                if (existed) restoreBackup(finalPath);
                return false;
            }
        }

        wr::p("PERSIST", finalPath.string() + (existed ? " atualizado." : " criado."), "Green");
        return true;
    } catch (const std::exception& e) {
        wr::p("PERSIST", finalPath.string() + " exception: " + e.what(), "Red");
        restoreBackup(finalPath);
        return false;
    } catch (...) {
        wr::p("PERSIST", finalPath.string() + " unknown exception", "Red");
        restoreBackup(finalPath);
        return false;
    }
}

} // namespace Persist
