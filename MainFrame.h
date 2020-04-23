#pragma once
#include <wx/wx.h>
#include "config.h"
#include "Canvas.h"
#include "RenderTimer.h"

class MainFrame: public wxFrame 
{
public:
	MainFrame(wxString title);
    Canvas* getCanvas() {return m_canvas;}

private:
	Canvas* m_canvas;
    wxButton* m_start_simulation_button;
    wxButton* m_stop_simulation_button;
    wxButton* m_reset_simulation_button;
    RenderTimer* m_timer;

    void onClose(wxCloseEvent& e);
    void onStartButtonClicked(wxCommandEvent& e);
    void onStopButtonClicked(wxCommandEvent& e);
    void onResetButtonClicked(wxCommandEvent& e);
};