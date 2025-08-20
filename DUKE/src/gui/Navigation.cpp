#include "gui/Navigation.h"
#include <cctype>

namespace duke {
namespace gui {

void ClearScreenWidget::render(std::ostream& out) const {
    out << "\033[2J\033[1;1H";
}

MenuKeyWidget::MenuKeyWidget(std::vector<std::string> opts,
                             std::vector<char> keys,
                             std::function<void(int)> onSelect)
    : m_opts(std::move(opts)),
      m_keys(std::move(keys)),
      m_onSelect(std::move(onSelect)) {}

void MenuKeyWidget::render(std::ostream& out) const {
    for (size_t i = 0; i < m_opts.size(); ++i) {
        out << m_keys[i] << ") " << m_opts[i] << "\n";
    }
    out << "> ";
}

void MenuKeyWidget::onKey(char c) {
    char u = static_cast<char>(std::toupper(c));
    for (size_t i = 0; i < m_keys.size(); ++i) {
        if (u == static_cast<char>(std::toupper(m_keys[i]))) {
            if (m_onSelect) m_onSelect(static_cast<int>(i));
            return;
        }
    }
}

MenuWidget::MenuWidget(std::vector<std::string> opts,
                       std::function<void(int)> onSelect)
    : m_opts(std::move(opts)),
      m_onSelect(std::move(onSelect)) {}

void MenuWidget::render(std::ostream& out) const {
    for (size_t i = 0; i < m_opts.size(); ++i) {
        out << i + 1 << ") " << m_opts[i] << "\n";
    }
    out << "> ";
}

void MenuWidget::onInput(int idx) {
    if (idx >= 1 && static_cast<size_t>(idx) <= m_opts.size()) {
        if (m_onSelect) m_onSelect(idx - 1);
    }
}

MainMenuWidget::MainMenuWidget(std::vector<std::string> opts,
                               std::vector<std::string> tooltips,
                               std::vector<bool> required,
                               std::function<void(int)> onSelect)
    : m_opts(std::move(opts)),
      m_tooltips(std::move(tooltips)),
      m_required(std::move(required)),
      m_onSelect(std::move(onSelect)) {
    for (size_t i = 0; i < m_opts.size(); ++i) {
        m_filteredIdx.push_back(static_cast<int>(i));
    }
}

void MainMenuWidget::render(std::ostream& out) const {
    for (size_t pos = 0; pos < m_filteredIdx.size(); ++pos) {
        int i = m_filteredIdx[pos];
        out << pos + 1 << ") " << m_opts[i];
        if (i < static_cast<int>(m_required.size()) && m_required[i]) {
            out << " *";
        }
        out << " - " << m_tooltips[i] << "\n";
    }
    out << "> ";
}

void MainMenuWidget::onInput(int idx) {
    if (idx >= 1 && static_cast<size_t>(idx) <= m_filteredIdx.size()) {
        if (m_onSelect) m_onSelect(m_filteredIdx[idx - 1]);
    }
}

void MainMenuWidget::filter(const std::string& term) {
    m_filteredIdx.clear();
    for (size_t i = 0; i < m_opts.size(); ++i) {
        std::string opt = m_opts[i];
        std::string t = term;
        for (auto& c : opt) c = static_cast<char>(std::tolower(c));
        for (auto& c : t) c = static_cast<char>(std::tolower(c));
        if (opt.find(t) != std::string::npos) {
            m_filteredIdx.push_back(static_cast<int>(i));
        }
    }
}

BreadcrumbWidget::BreadcrumbWidget(const std::vector<std::string>& trail)
    : m_trail(trail) {}

void BreadcrumbWidget::render(std::ostream& out) const {
    for (size_t i = 0; i < m_trail.size(); ++i) {
        if (i > 0) out << " > ";
        out << m_trail[i];
    }
    out << '\n';
}

} // namespace gui
} // namespace duke

