#include "MainFrame.h"

MainFrame::MainFrame(wxString title):
        wxFrame(nullptr, wxID_ANY, title),
        m_main_panel{new wxPanel(this)},
        m_menu_panel{new wxPanel(m_main_panel)},
        m_canvas{new Canvas(m_main_panel)},
        m_start_simulation_button{new wxButton(m_menu_panel, wxID_ANY, "Start simulation")},
        m_stop_simulation_button{new wxButton(m_menu_panel, wxID_ANY, "Pause simulation")},
        m_reset_simulation_button{new wxButton(m_menu_panel, wxID_ANY, "Generate random")},
        m_show_arrows_checkbox{new wxCheckBox(m_menu_panel, wxID_ANY, "Show velocity")},
        m_timer{new RenderTimer(m_canvas, config::kfps_max)}
{
    wxBoxSizer* bsizer_main = new wxBoxSizer(wxHORIZONTAL);
    m_main_panel->SetSizer(bsizer_main);
    bsizer_main->Add(m_canvas, 1, wxEXPAND);
    bsizer_main->Add(m_menu_panel, 0);

    wxBoxSizer* bsizer_menu = new wxBoxSizer(wxVERTICAL);
    m_menu_panel->SetSizer(bsizer_menu);
    bsizer_menu->Add(m_start_simulation_button, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
    bsizer_menu->Add(m_stop_simulation_button, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
    bsizer_menu->Add(m_reset_simulation_button, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
    bsizer_menu->Add(m_show_arrows_checkbox, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);

    m_start_simulation_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onStartButtonClicked, this);
    m_stop_simulation_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onStopButtonClicked, this);
    m_reset_simulation_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onResetButtonClicked, this);
    m_show_arrows_checkbox->Bind(wxEVT_CHECKBOX, &MainFrame::onCheckBoxChecked, this);
}

MainFrame::~MainFrame()
{
    m_start_simulation_button->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onStartButtonClicked, this);
    m_stop_simulation_button->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onStopButtonClicked, this);
    m_reset_simulation_button->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onResetButtonClicked, this);
    m_show_arrows_checkbox->Unbind(wxEVT_CHECKBOX, &MainFrame::onCheckBoxChecked, this);
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

void MainFrame::onCheckBoxChecked(wxCommandEvent& e)
{
    if (m_show_arrows_checkbox->IsChecked()) {m_canvas->setDrawArrows(true);}
    else {m_canvas->setDrawArrows(false);}
}