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
    dc.SetBrush(*wxBLUE_BRUSH);
    for (auto&& obj: m_objects)
    {
        dc.DrawCircle(obj.getPosition(), obj.getRadius());
    }
}

void Canvas::onTimerNotify()
{
    moveObjects();
    Refresh();
}

void Canvas::generateRandomObjects(size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        wxRealPoint random_pos(
            rand() % static_cast<int>(this->GetSize().GetWidth()-2*config::kball_radius) + config::kball_radius, 
            rand() % static_cast<int>(GetSize().GetHeight()-2*config::kball_radius) + config::kball_radius);
        wxRealPoint random_vel(
            static_cast<double>(rand()) / static_cast<double>(RAND_MAX), 
            static_cast<double>(rand()) / static_cast<double>(RAND_MAX));

        m_objects.push_back(std::move(Object(random_pos, random_vel)));
    }
}

void Canvas::clearObjects()
{
    m_objects.clear();
}

void Canvas::moveObjects() 
{
    for (auto&& o1: m_objects)
    {
        for (auto&& o2: m_objects)
        {
            if (&o1 != &o2) {o1.checkObjectCollision(o2);} // total brute force. TODO fix that in future?
        }
        o1.checkBorderCollision(GetSize());
        o1.move();
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