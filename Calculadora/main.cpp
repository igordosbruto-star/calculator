// ==========================================
// Arquivo: main.cpp
// Descrição: Ponto de entrada minimalista
// ==========================================

#include "Debug.h"
#include "App.h"

int main() {
    wr::p("MAIN", "Iniciando..", "Green");
    std::cout << "\n";

    App app;
    app.iniciar();

    std::cout << "\n";
    wr::p("MAIN", "Finalizando..", "Green");
    return 0;
}
