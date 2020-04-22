#pragma once
#include <wx/wx.h>
#include <wx/timer.h>
#include "Canvas.h"

class RenderTimer: public wxTimer
{
public:
    RenderTimer(Canvas* canvas, unsigned int fps):
            m_canvas{canvas},
            m_fps{fps}
    {}

    void Notify() override {m_canvas->onTimerNotify();}
    void start() { wxTimer::Start(static_cast<unsigned int>(1000/m_fps));}

private:
    Canvas* m_canvas;
    unsigned int m_fps;
};