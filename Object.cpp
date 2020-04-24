#define _USE_MATH_DEFINES
#include "Object.h"
#include <cmath>

Object::Object(): //TODO fix thiis abysmal pathetic way of construction 
        m_position{wxPoint(20, 20)}
{
    m_velocity[0] = 0.2;
    m_velocity[1] = 0.3;
}

Object::Object(const wxRealPoint& position): // TODO same as above.
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

void Object::checkBorderCollision(const wxSize& canvas_size)
{
    if (m_velocity[0] > 0)
    {
        if (m_position.x + m_radius > canvas_size.GetWidth()) 
        { 
            m_position.x = canvas_size.GetWidth() - m_radius - 1.0;
            m_velocity[0] = -m_velocity[0]; 
        }
    }
    else if (m_velocity[0] < 0)
    {
        if (m_position.x - m_radius < 0) 
        { 
            m_position.x = m_radius + 1.0;
            m_velocity[0] = -m_velocity[0]; 
        }
    }

    if (m_velocity[1] > 0)
    {
        if (m_position.y + m_radius > canvas_size.GetHeight()) 
        { 
            m_position.y = canvas_size.GetHeight() - m_radius - 1.0;
            m_velocity[1] = -m_velocity[1]; 
        }
    }
    else if (m_velocity[1] < 0)
    {
        if (m_position.y - m_radius < 0) 
        { 
            m_velocity[1] = -m_velocity[1]; 
            m_position.y = m_radius + 1.0;
        }
    }
}

void Object::checkObjectCollision(const std::vector<std::unique_ptr<Object>>& list)
{
    for (auto&& obj: list)
    {
        if (obj.get() == this) { continue; }
        if (obj->m_after_collision) 
        {
            obj->m_after_collision = false;
            continue;
        }

        double radius_sum = m_radius + obj->m_radius;
        double distance_x = fabs(m_position.x - obj->m_position.x);
        double distance_y = fabs(m_position.y - obj->m_position.y);
        double distance = sqrt(distance_x*distance_x + distance_y*distance_y);
        
        if (distance < radius_sum)
        {
            obj->m_after_collision = true;

        }
    }
}