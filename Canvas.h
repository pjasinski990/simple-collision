#pragma once
#include <wx/wx.h>

class Canvas: public wxPanel 
{
public:
    Canvas(wxWindow* parent);
    void render(wxDC& dc);
    void onTimerNotify();

private:
	void onPaint(wxPaintEvent& e);
	void onErase(wxEraseEvent& e);

    wxColour m_background_colour;
};