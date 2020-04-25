#pragma once
#include <vector>
#include <memory>
#include <wx/wx.h>
#include "Object.h"

class Canvas: public wxPanel 
{
public:
    Canvas(wxWindow* parent);
    void generateRandomObjects(size_t n);
    void clearObjects();
    void render(wxDC& dc);
    void onTimerNotify();

private:
    void moveObjects();
	void onPaint(wxPaintEvent& e);
	void onErase(wxEraseEvent& e);

    std::vector<Object> m_objects;
    wxColour m_background_colour;
};