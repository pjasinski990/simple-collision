#define _USE_MATH_DEFINES
#include "Object.h"
#include <cmath>

Object::Object(const wxRealPoint& position, const wxRealPoint& velocity): // TODO same as above.
        m_position{position},
        m_velocity{velocity}
{
}

void Object::move()
{
    double speed = sqrt(pow(m_velocity.x, 2) + pow(m_velocity.y, 2));
    if (speed)
    {
        double x_part = m_velocity.x/(abs(m_velocity.x)+abs(m_velocity.y)) * speed;
        double y_part = m_velocity.y/(abs(m_velocity.x)+abs(m_velocity.y)) * speed;

        m_position.x += x_part * config::ktime_step_millis;
        m_position.y += y_part * config::ktime_step_millis;
    } 
} 

void Object::checkBorderCollision(const wxSize& canvas_size)
{
    if (m_velocity.x > 0)
    {
        if (m_position.x + m_radius > canvas_size.GetWidth()) 
        { 
            m_position.x = canvas_size.GetWidth() - m_radius - 1.0;
            m_velocity.x = -m_velocity.x; 
        }
    }
    else if (m_velocity.x < 0)
    {
        if (m_position.x - m_radius < 0) 
        { 
            m_position.x = m_radius + 1.0;
            m_velocity.x = -m_velocity.x; 
        }
    }

    if (m_velocity.y > 0)
    {
        if (m_position.y + m_radius > canvas_size.GetHeight()) 
        { 
            m_position.y = canvas_size.GetHeight() - m_radius - 1.0;
            m_velocity.y = -m_velocity.y; 
        }
    }
    else if (m_velocity.y < 0)
    {
        if (m_position.y - m_radius < 0) 
        { 
            m_velocity.y = -m_velocity.y; 
            m_position.y = m_radius + 1.0;
        }
    }
}

void Object::checkObjectCollision(Object& o)
{
    double radius_sum = m_radius + o.m_radius;
    double distance_x = fabs(m_position.x - o.m_position.x);
    double distance_y = fabs(m_position.y - o.m_position.y);
    double distance = sqrt(distance_x*distance_x + distance_y*distance_y);

    if (distance < radius_sum)
    {
        // Dynamic resolution, assuming equal masses 
        wxRealPoint temp_v1 = m_velocity - o.m_velocity;
        wxRealPoint temp_v2 = o.m_velocity - m_velocity;
        wxRealPoint temp_pos1 = m_position - o.m_position;
        wxRealPoint temp_pos2 = o.m_position - m_position;

        double scalar1 = temp_v1.x*temp_pos1.x + temp_v1.y*temp_pos1.y;
        double scalar2 = temp_v2.x*temp_pos2.x + temp_v2.y*temp_pos2.y;

        m_velocity.x -= temp_pos1.x * (scalar1/distance/distance);
        m_velocity.y -= temp_pos1.y * (scalar1/distance/distance);
        o.m_velocity.x -= temp_pos2.x * (scalar2/distance/distance);
        o.m_velocity.y -= temp_pos2.y * (scalar2/distance/distance);

        // Static resolution
        double d = 0.5 * (distance - radius_sum);
        m_position.x -= d * (m_position.x - o.m_position.x) / distance;
        m_position.y -= d * (m_position.y - o.m_position.y) / distance;
        o.m_position.x += d * (m_position.x - o.m_position.x) / distance;
        o.m_position.y += d * (m_position.y - o.m_position.y) / distance;
    }
}