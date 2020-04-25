#pragma once

#include "config.h"
#include <array>
#include <vector>
#include <memory>
#include <wx/wx.h>

class Object
{
public:
    Object(const wxRealPoint& position, const wxRealPoint& velocity);
    double getRadius() const {return m_radius;}
    const wxRealPoint& getPosition() const {return m_position;}
    void move();
    void checkBorderCollision(const wxSize& canvas_size);
    void checkObjectCollision(Object& o);

private:
    wxRealPoint m_position;
    wxRealPoint m_velocity;
    double m_radius = config::kball_radius;
};