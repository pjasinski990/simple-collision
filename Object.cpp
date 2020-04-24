#include "Object.h"

Object::Object(): 
        m_position{wxPoint(20, 20)}
{
    m_velocity[0] = 0.2;
    m_velocity[1] = 0.3;
}

Object::Object(const wxRealPoint& position): 
        m_position{position}
{
    m_velocity[0] = 0.6;
    m_velocity[1] = -0.3;
}

void Object::move()
{
    double speed = sqrt(pow(m_velocity[0], 2) + pow(m_velocity[1], 2));
    if (speed)
    {
        double x_part = m_velocity[0]/(abs(m_velocity[0])+abs(m_velocity[1])) * speed;
        double y_part = m_velocity[1]/(abs(m_velocity[0])+abs(m_velocity[1])) * speed;

        m_position.x += x_part * config::ktime_step_millis;
        m_position.y += y_part * config::ktime_step_millis;
    } 
} 

void Object::check_border_collision(const wxSize& canvas_size)
{
    if (m_velocity[0] > 0)
    {
        if (m_position.x + m_radius > canvas_size.GetWidth()) { m_velocity[0] = -m_velocity[0]; }
    }
    else if (m_velocity[0] < 0)
    {
        if (m_position.x - m_radius < 0) { m_velocity[0] = -m_velocity[0]; }
    }

    if (m_velocity[1] > 0)
    {
        if (m_position.y + m_radius > canvas_size.GetHeight()) { m_velocity[1] = -m_velocity[1]; }
    }
    else if (m_velocity[1] < 0)
    {
        if (m_position.y - m_radius < 0) { m_velocity[1] = -m_velocity[1]; }
    }
}