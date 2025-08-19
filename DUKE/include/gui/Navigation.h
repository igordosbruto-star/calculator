#pragma once

#include <vector>
#include <string>
#include <functional>
#include <ostream>

namespace duke {
namespace gui {

// ==========================================
// Widget: ClearScreenWidget
// Descrição: limpa a área de saída.
// Exemplo de uso:
//   ClearScreenWidget w; w.render(std::cout);
// ==========================================
class ClearScreenWidget {
public:
    void render(std::ostream& out) const;
};

// ==========================================
// Widget: MenuKeyWidget
// Descrição: exibe opções com teclas associadas e dispara
//            callback ao selecionar.
// Exemplo de uso:
//   MenuKeyWidget w(opts, keys, [](int i){ /*...*/ });
//   w.render(std::cout);
//   w.onKey('a');
// ==========================================
class MenuKeyWidget {
public:
    MenuKeyWidget(std::vector<std::string> opts,
                  std::vector<char> keys,
                  std::function<void(int)> onSelect);

    void render(std::ostream& out) const;
    void onKey(char c);

private:
    std::vector<std::string> m_opts;
    std::vector<char> m_keys;
    std::function<void(int)> m_onSelect;
};

// ==========================================
// Widget: MenuWidget
// Descrição: exibe menu numerado e aciona callback
//            ao receber índice válido.
// Exemplo de uso:
//   MenuWidget w(opts, [](int i){ /*...*/ });
//   w.render(std::cout);
//   w.onInput(1);
// ==========================================
class MenuWidget {
public:
    MenuWidget(std::vector<std::string> opts,
               std::function<void(int)> onSelect);

    void render(std::ostream& out) const;
    void onInput(int idx);

private:
    std::vector<std::string> m_opts;
    std::function<void(int)> m_onSelect;
};

// ==========================================
// Widget: BreadcrumbWidget
// Descrição: exibe trilha de navegação.
// Exemplo de uso:
//   BreadcrumbWidget w(trail); w.render(std::cout);
// ==========================================
class BreadcrumbWidget {
public:
    explicit BreadcrumbWidget(const std::vector<std::string>& trail);
    void render(std::ostream& out) const;

private:
    const std::vector<std::string>& m_trail;
};

} // namespace gui
} // namespace duke

