#pragma once
#include <vector>
#include <memory>
#include <wx/wx.h>
#include "Object.h"

class Canvas: public wxPanel 
{
public:
    Canvas(wxWindow* parent);
    void setDrawArrows(bool flag);
    void generateRandomObjects(size_t n);
    void clearObjects();
    void render(wxDC& dc);
    double getTotalEnergy() const;
    void onTimerNotify();

private:
    bool m_draw_arrows = false;
    void moveObjects();
	void onPaint(wxPaintEvent& e);
	void onErase(wxEraseEvent& e);

    std::vector<std::unique_ptr<Object>> m_objects;
    wxColour m_background_colour;
};