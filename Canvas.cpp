#include "Canvas.h"

Canvas::Canvas(wxWindow* parent):
        wxPanel(parent),
        m_background_colour{70, 70, 70}
{
    Bind(wxEVT_PAINT, &Canvas::onPaint, this);
    Bind(wxEVT_ERASE_BACKGROUND, &Canvas::onErase, this);
    SetBackgroundColour(m_background_colour);

    m_objects.push_back(std::unique_ptr<Object>(new Object(wxRealPoint(120, 120), wxRealPoint(0.4, 0))));
    m_objects.push_back(std::unique_ptr<Object>(new Object(wxRealPoint(300, 125), wxRealPoint(-0.3, 0))));
    m_objects.push_back(std::unique_ptr<Object>(new Object(wxRealPoint(400, 150), wxRealPoint(-0.3, 0))));
    m_objects.push_back(std::unique_ptr<Object>(new Object(wxRealPoint(100, 300), wxRealPoint(-0.3, 0))));
    m_objects.push_back(std::unique_ptr<Object>(new Object(wxRealPoint(300, 400), wxRealPoint(-0.3, 0))));
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
    for (auto&& o1: m_objects)
    {
        for (auto&& o2: m_objects)
        {
            if (o1.get() == o2.get()) {continue;}
            o1->checkObjectCollision(*o2); // total brute force. TODO fix that in future?
        }
        o1->checkBorderCollision(GetSize());
        o1->move();
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