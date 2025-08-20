// ==========================================
// Arquivo: main_wx.cpp
// Descrição: Ponto de entrada para interface wxWidgets
// ==========================================

#include <wx/wx.h>

namespace duke {
namespace gui {

class MainApp : public wxApp {
public:
    bool OnInit() override {
        wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Duke Calculator");
        frame->Show(true);
        return true;
    }
};

} // namespace gui
} // namespace duke

#ifndef UNIT_TEST
wxIMPLEMENT_APP(duke::gui::MainApp);
#endif // UNIT_TEST

