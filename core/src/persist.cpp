#include "core/persist.h"

namespace Persist {

bool save(const std::string& path, const std::vector<MaterialDTO>& v,
          int schemaVersion, const std::string& baseDir) {
    std::string ext = fs::path(path).extension().string();
    if (ext == ".csv") return saveCSV(path, v, baseDir);
    if (ext == ".xml") return saveXML(path, v, baseDir);
    return saveJSON(path, v, schemaVersion, baseDir);
}

bool load(const std::string& path, std::vector<MaterialDTO>& out,
          int* out_schema_version, const std::string& baseDir) {
    std::string ext = fs::path(path).extension().string();
    if (ext == ".csv") return loadCSV(path, out, baseDir);
    if (ext == ".xml") return loadXML(path, out, baseDir);
    return loadJSON(path, out, out_schema_version, baseDir);
}

} // namespace Persist

