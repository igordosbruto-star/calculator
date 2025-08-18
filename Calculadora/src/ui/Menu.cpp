#include "ui/Menu.h"
#include <limits>

namespace ui {

void clearScreen(std::ostream& out) {
    out << "\033[2J\033[1;1H";
}

void renderBreadcrumb(const std::vector<std::string>& trail,
                      std::ostream& out) {
    for (size_t i = 0; i < trail.size(); ++i) {
        if (i > 0) out << " > ";
        out << trail[i];
    }
    out << '\n';
}

int promptMenu(const std::vector<std::string>& options,
               std::istream& in,
               std::ostream& out) {
    for (size_t i = 0; i < options.size(); ++i) {
        out << i + 1 << ") " << options[i] << "\n";
    }
    out << "> ";
    int choice = 0;
    while (!(in >> choice) || choice < 1 || choice > static_cast<int>(options.size())) {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        out << "Opcao invalida. Tente novamente: ";
    }
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
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

