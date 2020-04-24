#pragma once
#include <wx/wx.h>
#include <wx/timer.h>
#include "config.h"
#include "Canvas.h"

class RenderTimer: public wxTimer
{
public:
    RenderTimer(Canvas* canvas, unsigned int fps):
            m_canvas{canvas},
            m_fps{fps}
    {}

    void Notify() override {m_canvas->onTimerNotify();}
    void start() { wxTimer::Start(static_cast<unsigned int>(config::ktime_step_millis));}

private:
    Canvas* m_canvas;
    unsigned int m_fps;
};