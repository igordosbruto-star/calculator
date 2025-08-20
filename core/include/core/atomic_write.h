#pragma once

#include <filesystem>
#include <string>
#include "core/Debug.h"

namespace Persist {

namespace fs = std::filesystem;

bool hasWritePermission(const fs::path& p);
bool restoreBackup(const fs::path& finalPath);
bool atomicWrite(const fs::path& finalPath, const std::string& content);

} // namespace Persist
