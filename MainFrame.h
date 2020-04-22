#pragma once
#include "config.h"
#include <wx/wx.h>
#include "Canvas.h"
#include "RenderTimer.h"

class MainFrame: public wxFrame 
{
public:
	MainFrame(wxString title):
            wxFrame(nullptr, wxID_ANY, title),
            m_canvas{new Canvas(this)},
            m_timer{new RenderTimer(m_canvas, config::kfps_max)}
    {}

    Canvas* getPanel() {return m_canvas;}

private:
	Canvas* m_canvas;
    RenderTimer* m_timer;
    void onClose(wxCloseEvent& e);
};