#include "ui/Menu.h"
#include <limits>
#include <cctype>
#include "gui/Navigation.h"
namespace duke {

namespace ui {

void clearScreen(std::ostream& out) {
    gui::ClearScreenWidget w;
    w.render(out);
}

void renderBreadcrumb(const std::vector<std::string>& trail,
                      std::ostream& out) {
    gui::BreadcrumbWidget bc(trail);
    bc.render(out);
}

int promptMenu(const std::vector<std::string>& options,
               std::istream& in,
               std::ostream& out) {
    int escolha = -1;
    gui::MenuWidget menu(options, [&](int idx){ escolha = idx + 1; });
    while (escolha < 0) {
        menu.render(out);
        if (!(in >> escolha)) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            out << "Opcao invalida. Tente novamente: ";
            escolha = -1;
            continue;
        }
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (escolha < 1 || escolha > static_cast<int>(options.size())) {
            out << "Opcao invalida. Tente novamente: ";
            escolha = -1;
        } else {
            menu.onInput(escolha);
        }
    }
    return escolha;
}

int promptMenuKey(const std::vector<std::string>& options,
                  const std::vector<char>& keys,
                  std::istream& in,
                  std::ostream& out) {
    if (options.size() != keys.size()) return -1;
    int escolha = -1;
    gui::MenuKeyWidget menu(options, keys, [&](int idx){ escolha = idx; });
    while (escolha < 0) {
        menu.render(out);
        std::string line;
        std::getline(in, line);
        if (line == "?") {
            out << "Digite a letra correspondente a opcao desejada.\n";
            continue;
        }
        if (!line.empty()) {
            menu.onKey(line[0]);
        }
        if (escolha < 0) out << "Opcao invalida. Tente novamente.\n";
    }
    return escolha;
}

int readInt(const std::string& prompt,
            std::istream& in,
            std::ostream& out) {
    int value = 0;
    while (true) {
        out << prompt;
        if (in >> value) {
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        out << "Entrada invalida. Tente novamente.\n";
    }
}

double readDouble(const std::string& prompt,
                  std::istream& in,
                  std::ostream& out) {
    double value = 0.0;
    while (true) {
        out << prompt;
        if (in >> value) {
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        out << "Entrada invalida. Tente novamente.\n";
    }
}

std::string readString(const std::string& prompt,
                       std::istream& in,
                       std::ostream& out) {
    out << prompt;
    std::string line;
    std::getline(in, line);
    return line;
}

} // namespace ui

} // namespace duke
