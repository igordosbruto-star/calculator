#include "finance/Repo.h"
#include "finance/Serialize.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>

namespace finance {

using nlohmann::json;

bool FinanceRepo::load(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open())
        return false;
    json j;
    f >> j;
    schema_version = j.value("schema_version", 1);
    items.clear();
    if (j.contains("items"))
        j.at("items").get_to(items);
    return true;
}

bool FinanceRepo::save(const std::string& path) const {
    std::ofstream f(path);
    if (!f.is_open())
        return false;
    json j;
    j["schema_version"] = schema_version;
    j["items"] = items;
    f << j.dump(2);
    return true;
}

std::string FinanceRepo::nextId() const {
    using namespace std::chrono;
    auto now = system_clock::now();
    std::time_t tt = system_clock::to_time_t(now);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &tt);
#else
    localtime_r(&tt, &tm);
#endif
    char date_buf[11];
    std::strftime(date_buf, sizeof(date_buf), "%Y-%m-%d", &tm);
    std::string date = date_buf;

    int seq = 0;
    for (const auto& l : items) {
        if (l.data == date)
            ++seq;
    }
    std::ostringstream oss;
    oss << "FIN-" << date << "-" << std::setw(4) << std::setfill('0') << (seq + 1);
    return oss.str();
}

namespace {
// Verifica se a data está no formato ISO AAAA-MM-DD
bool isIsoDate(const std::string& s) {
    if (s.size() != 10 || s[4] != '-' || s[7] != '-') return false;
    std::tm tm{};
    std::istringstream iss(s);
    iss >> std::get_time(&tm, "%Y-%m-%d");
    return !iss.fail();
}
} // namespace

bool FinanceRepo::add(const Lancamento& l) {
    if (l.valor <= 0.0 || !isIsoDate(l.data))
        return false;
    items.push_back(l);
    return true;
}

bool FinanceRepo::remove(const std::string& id) {
    auto it = std::remove_if(items.begin(), items.end(), [&](const Lancamento& l) { return l.id == id; });
    if (it == items.end())
        return false;
    items.erase(it, items.end());
    return true;
}

std::vector<Lancamento> FinanceRepo::query(const Filtro& f) const {
    std::vector<Lancamento> result;
    for (const auto& l : items) {
        if (f.tipo && l.tipo != *f.tipo) continue;
        if (f.subtipo && l.subtipo != *f.subtipo) continue;
        if (f.conta && l.conta != *f.conta) continue;
        if (f.dt_ini && l.data < *f.dt_ini) continue;
        if (f.dt_fim && l.data > *f.dt_fim) continue;
        if (f.entrada && l.entrada != *f.entrada) continue;
        bool tags_ok = true;
        for (const auto& t : f.tags_all) {
            if (std::find(l.tags.begin(), l.tags.end(), t) == l.tags.end()) {
                tags_ok = false;
                break;
            }
        }
        if (!tags_ok) continue;
        result.push_back(l);
    }
    return result;
}

double FinanceRepo::sum(const Filtro& f) const {
    double total = 0.0;
    auto vec = query(f);
    for (const auto& l : vec) {
        total += l.entrada ? l.valor : -l.valor;
    }
    return total;
}

} // namespace finance

