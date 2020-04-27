#include "MainFrame.h"

MainFrame::MainFrame(wxString title):
        wxFrame(nullptr, wxID_ANY, title),
        m_main_panel{new wxPanel(this)},
        m_canvas{new Canvas(this)},
        m_start_simulation_button{new wxButton(this, wxID_ANY, "Start simulation")},
        m_stop_simulation_button{new wxButton(this, wxID_ANY, "Pause simulation")},
        m_reset_simulation_button{new wxButton(this, wxID_ANY, "Generate random")},
        m_timer{new RenderTimer(m_canvas, config::kfps_max)}
{
    wxBoxSizer* bsizer_frame = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer_main = new wxBoxSizer(wxVERTICAL);
    bsizer_frame->Add(m_main_panel, 1, wxEXPAND);
    m_main_panel->SetSizer(bsizer_main);

    /*
    wxBoxSizer* bsizerMenu = new wxBoxSizer(wxVERTICAL);

    bsizerMenu->Add(m_start_simulation_button, 0, wxALIGN_CENTER);
    bsizerMenu->Add(m_stop_simulation_button, 0, wxALIGN_CENTER);
    bsizerMenu->Add(m_reset_simulation_button, 0, wxALIGN_CENTER);

    SetSizer(bsizerMain);

    bsizerMain->Add(m_canvas, 1, wxEXPAND);
    bsizerMain->Add(bsizerMenu, 0);

    // Binding event handlers
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onClose, this);
    m_start_simulation_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onStartButtonClicked, this);
    m_stop_simulation_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onStopButtonClicked, this);
    m_reset_simulation_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onResetButtonClicked, this);
    */
}

void MainFrame::onClose(wxCloseEvent& e)
{
    m_timer->Stop();
    e.Skip();
}

void MainFrame::onStartButtonClicked(wxCommandEvent& e)
{
    m_timer->start();
}

void MainFrame::onStopButtonClicked(wxCommandEvent& e)
{
    m_timer->Stop();
}

void MainFrame::onResetButtonClicked(wxCommandEvent& e)
{
    m_timer->Stop();
    m_canvas->clearObjects();
    m_canvas->generateRandomObjects(config::kballs_count);
    m_canvas->Refresh();
}