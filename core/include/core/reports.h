#pragma once

#include <string>
#include <utility>

#include "finance/Repo.h"

namespace core {
namespace reports {

struct Summary {
    double entradas = 0.0;
    double saidas = 0.0;
};

Summary monthlySummary(const finance::FinanceRepo& repo, int year, int month);
std::pair<std::string, std::string> generateMonthlyReport(const finance::FinanceRepo& repo, int year, int month);

} // namespace reports
} // namespace core

