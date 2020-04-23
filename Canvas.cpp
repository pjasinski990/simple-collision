#include "Canvas.h"

Canvas::Canvas(wxWindow* parent):
        wxPanel(parent),
        m_background_colour{70, 70, 70}
{
    Bind(wxEVT_PAINT, &Canvas::onPaint, this);
    Bind(wxEVT_ERASE_BACKGROUND, &Canvas::onErase, this);
    SetBackgroundColour(m_background_colour);
}

void Canvas::render(wxDC& dc)
{
    dc.Clear();
}

void Canvas::onTimerNotify()
{
    
}

void Canvas::onPaint(wxPaintEvent& e)
{
    wxPaintDC dc(this);
    render(dc);
    e.Skip();
}

void Canvas::onErase(wxEraseEvent& e)
{
    e.Skip();
}