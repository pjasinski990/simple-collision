#pragma once
#include <vector>
#include <memory>
#include <wx/wx.h>
#include "Object.h"

class Canvas: public wxPanel 
{
public:
    Canvas(wxWindow* parent);
    void render(wxDC& dc);
    void onTimerNotify();

private:
    void moveObjects();
	void onPaint(wxPaintEvent& e);
	void onErase(wxEraseEvent& e);

    std::vector<std::unique_ptr<Object>> m_objects;
    size_t m_object_count;
    wxColour m_background_colour;
};