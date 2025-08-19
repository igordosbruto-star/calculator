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

