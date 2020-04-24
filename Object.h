#pragma once

#include "config.h"
#include <array>
#include <wx/wx.h>

class Object
{
public:
    Object();
    Object(const wxRealPoint& position);
    double getRadius() const {return m_radius;}
    const wxRealPoint& getPosition() const {return m_position;}
    void move();
    virtual void check_border_collision(const wxSize& canvas_size);

private:
    wxRealPoint m_position;
    std::array<double, 2> m_velocity;
    double m_radius = 12.0;
};