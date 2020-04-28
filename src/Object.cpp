#include "Object.h"

wxPoint rotate(const wxPoint& p, double phi)
{
    double xp = cos(phi)*p.x - sin(phi)*p.y;
    double yp = sin(phi)*p.x + cos(phi)*p.y;
    return wxPoint(xp, yp);
}

Object::Object(const wxRealPoint& position, const wxRealPoint& velocity):
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

void Object::draw(wxDC& dc)
{
    dc.SetBrush(wxBrush(m_colour));
    dc.SetPen(wxPen(m_colour));
    dc.DrawCircle(getPosition(), getRadius());
}

void Object::drawArrow(wxDC& dc)
{
    dc.SetPen(wxPen(*wxRED, 2));
    dc.SetBrush(wxBrush(*wxRED));

    double vel = sqrt(getVelocity().x*getVelocity().x + getVelocity().y*getVelocity().y);
    wxRealPoint norm(getVelocity().x / vel, getVelocity().y/vel);

    wxPointList triangle;
    double phi = atan2(getVelocity().y, getVelocity().x);

    wxPoint p1(rotate(wxPoint(-4, -3), phi));
    wxPoint p2(rotate(wxPoint(4, 0), phi));
    wxPoint p3(rotate(wxPoint(-4, 3), phi));
    triangle.Append(&p1);
    triangle.Append(&p2);
    triangle.Append(&p3);

    wxPoint line_end(getPosition() + norm*m_radius + getVelocity()*config::karrowlength_scaling_factor);
    dc.DrawLine(getPosition()+norm*m_radius, line_end);
    dc.DrawPolygon(&triangle, line_end.x, line_end.y);
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
        // Dynamic response, assuming equal masses 
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

        // Static response
        double d = 0.5 * (distance - radius_sum);
        m_position.x -= d * (m_position.x - o.m_position.x) / distance;
        m_position.y -= d * (m_position.y - o.m_position.y) / distance;
        o.m_position.x += d * (m_position.x - o.m_position.x) / distance;
        o.m_position.y += d * (m_position.y - o.m_position.y) / distance;
    }
}