#include "App.h"

IMPLEMENT_APP(App);
DECLARE_APP(App);

bool App::OnInit()
{
	m_main_frame = new MainFrame(wxT("simple collision"));
	SetTopWindow(m_main_frame);
	m_main_frame->Show(true);
	m_main_frame->SetSize(wxSize(800, 600));
	m_main_frame->Center();
	m_main_frame->SetFocus();

	return true;
}