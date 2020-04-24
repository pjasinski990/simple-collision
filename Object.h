#pragma once

#include "config.h"
#include <array>
#include <vector>
#include <memory>
#include <wx/wx.h>

class Object
{
public:
    Object();
    Object(const wxRealPoint& position);
    double getRadius() const {return m_radius;}
    const wxRealPoint& getPosition() const {return m_position;}
    void move();
    void checkBorderCollision(const wxSize& canvas_size);
    void checkObjectCollision(const std::vector<std::unique_ptr<Object>>& list); // total brute force. TODO fix that in future?

private:
    wxRealPoint m_position;
    std::array<double, 2> m_velocity;
    double m_radius = 50.0;
    bool m_after_collision = false;
};