#pragma once
#include <wx/wx.h>
#include "config.h"
#include "Canvas.h"
#include "RenderTimer.h"

class MainFrame: public wxFrame 
{
public:
	MainFrame(wxString title):
            wxFrame(nullptr, wxID_ANY, title),
            m_canvas{new Canvas(this)},
            m_start_simulation_button{new wxButton(this, wxID_ANY, "Start simulation")},
            m_stop_simulation_button{new wxButton(this, wxID_ANY, "Pause simulation")},
            m_reset_simulation_button{new wxButton(this, wxID_ANY, "Reset simulation")},
            m_timer{new RenderTimer(m_canvas, config::kfps_max)}
    {
        wxBoxSizer* bsizerMain = new wxBoxSizer(wxHORIZONTAL);
        wxBoxSizer* bsizerMenu = new wxBoxSizer(wxVERTICAL);

        bsizerMenu->Add(m_start_simulation_button, 0, wxALIGN_CENTER);
        bsizerMenu->Add(m_stop_simulation_button, 0, wxALIGN_CENTER);
        bsizerMenu->Add(m_reset_simulation_button, 0, wxALIGN_CENTER);

        bsizerMain->Add(m_canvas, 1, wxEXPAND);
        bsizerMain->Add(bsizerMenu, 0);

        SetSizer(bsizerMain);
        m_timer->start();
        Show();
    }

    Canvas* getCanvas() {return m_canvas;}

private:
	Canvas* m_canvas;
    wxButton* m_start_simulation_button;
    wxButton* m_stop_simulation_button;
    wxButton* m_reset_simulation_button;

    RenderTimer* m_timer;
    void onClose(wxCloseEvent& e);
};