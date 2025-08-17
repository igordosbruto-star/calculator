#include "persist.h"
#include "modulos.h"

namespace Persist {

bool saveCutsCSV(const std::string& path, const std::vector<Corte>& cortes) {
    std::ostringstream oss;
    oss << "nome;largura;comprimento;area;subtotal\n";

    double total = 0.0;
    for (const auto& c : cortes) {
        std::string safe = c.capNome();
        for (auto& ch : safe) if (ch == ';') ch = ',';

        oss << safe << ';'
            << to_str_br(c.capLarg()) << ';'
            << to_str_br(c.capComp()) << ';'
            << to_str_br(c.capArea()) << ';'
            << to_str_br(c.capValor()) << "\n";
        total += c.capValor();
    }

    oss << "TOTAL;" << to_str_br(total) << "\n";
    return atomicWrite(fs::path(dataPath(path)), oss.str());
}

} // namespace Persist
