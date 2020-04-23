#include "MainFrame.h"

MainFrame::MainFrame(wxString title):
        wxFrame(nullptr, wxID_ANY, title),
        m_canvas{new Canvas(this)},
        m_start_simulation_button{new wxButton(this, wxID_ANY, "Start simulation")},
        m_stop_simulation_button{new wxButton(this, wxID_ANY, "Pause simulation")},
        m_reset_simulation_button{new wxButton(this, wxID_ANY, "Reset simulation")},
        m_timer{new RenderTimer(m_canvas, config::kfps_max)}
{
    // Sizers and layout
    wxBoxSizer* bsizerMain = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizerMenu = new wxBoxSizer(wxVERTICAL);

    bsizerMenu->Add(m_start_simulation_button, 0, wxALIGN_CENTER);
    bsizerMenu->Add(m_stop_simulation_button, 0, wxALIGN_CENTER);
    bsizerMenu->Add(m_reset_simulation_button, 0, wxALIGN_CENTER);

    bsizerMain->Add(m_canvas, 1, wxEXPAND);
    bsizerMain->Add(bsizerMenu, 0);
    SetSizer(bsizerMain);

    // Binding event handlers
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onClose, this);
    m_start_simulation_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onStartButtonClicked, this);
    m_stop_simulation_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onStopButtonClicked, this);
    m_reset_simulation_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onResetButtonClicked, this);

    m_timer->start();
    Show();
}

void MainFrame::onClose(wxCloseEvent& e)
{
    m_timer->Stop();
    e.Skip();
}

void MainFrame::onStartButtonClicked(wxCommandEvent& e)
{
    std::cout << "start" << std::endl;
}

void MainFrame::onStopButtonClicked(wxCommandEvent& e)
{
    std::cout << "stop" << std::endl;
}

void MainFrame::onResetButtonClicked(wxCommandEvent& e)
{
    std::cout << "reset" << std::endl;
}