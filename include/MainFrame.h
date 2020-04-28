#pragma once
#include <wx/wx.h>
#include "config.h"
#include "Canvas.h"
#include "RenderTimer.h"

class MainFrame: public wxFrame 
{
public:
	MainFrame(wxString title);
    ~MainFrame();

private:
    wxPanel* m_main_panel;
    wxPanel* m_menu_panel;
	Canvas* m_canvas;
    wxButton* m_start_simulation_button;
    wxButton* m_stop_simulation_button;
    wxButton* m_reset_simulation_button;
    wxCheckBox* m_show_arrows_checkbox;
    RenderTimer* m_timer;

    void onStartButtonClicked(wxCommandEvent& e);
    void onStopButtonClicked(wxCommandEvent& e);
    void onResetButtonClicked(wxCommandEvent& e);
    void onCheckBoxChecked(wxCommandEvent& e);
};