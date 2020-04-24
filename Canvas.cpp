#include "Canvas.h"

Canvas::Canvas(wxWindow* parent):
        wxPanel(parent),
        m_background_colour{70, 70, 70}
{
    Bind(wxEVT_PAINT, &Canvas::onPaint, this);
    Bind(wxEVT_ERASE_BACKGROUND, &Canvas::onErase, this);
    SetBackgroundColour(m_background_colour);

    m_objects.push_back(std::unique_ptr<Object>(new Object()));
    m_objects.push_back(std::unique_ptr<Object>(new Object(wxRealPoint(120, 120))));
}

void Canvas::render(wxDC& dc)
{
    dc.Clear();
    dc.SetBrush(*wxBLUE_BRUSH);
    for (auto&& obj: m_objects)
    {
        dc.DrawCircle(obj->getPosition(), obj->getRadius());
    }
}

void Canvas::onTimerNotify()
{
    moveObjects();
    Refresh();
}

void Canvas::moveObjects() 
{
    for (auto&& obj: m_objects)
    {
        obj->checkBorderCollision(GetSize());
        obj->checkObjectCollision(m_objects);
        obj->move();
    }
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