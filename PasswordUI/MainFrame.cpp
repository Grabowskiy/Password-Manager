#include "MainFrame.h"
#include <wx\wx.h>
#include <memory>
#include "blowfish.h"


int WIDTH = 600;
int HEIGHT = 500;

#define inputboxsize 200, 30


MainFrame::MainFrame(const std::string& title) : wxFrame(nullptr, wxID_ANY, title) 
{
	MainFrame::CreateConsol();
	MainFrame::BindControls();
	CreateStatusBar();
}

void MainFrame::CreateConsol() 
{
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Italic());
	wxFont mainFont(wxFontInfo(wxSize(0, 20)));
	wxFont helptextFont(wxFontInfo(wxSize(0, 12)));

	panel = new wxPanel(this);
	panel->SetBackgroundColour(wxColour(240, 240, 240));
	panel->SetFont(mainFont);

	passwordmanager = new wxStaticText(panel, wxID_ANY, "KEEP IT SAFE", wxPoint(0, 15), wxSize(WIDTH, -1), wxALIGN_CENTER_HORIZONTAL);
	passwordmanager->SetFont(headlineFont);

	username = new wxTextCtrl(panel, wxID_ANY, "website", wxPoint(25, 75), wxSize(inputboxsize));
	password = new wxTextCtrl(panel, wxID_ANY, "password", wxPoint(25, 125), wxSize(inputboxsize));
	filename = new wxTextCtrl(panel, wxID_ANY, "filename.txt", wxPoint(25, 175), wxSize(inputboxsize));

	file_helptext = new wxStaticText(panel, wxID_ANY, "Give the filename or the path of file", wxPoint(25, 205), wxSize(200, -1), wxALIGN_LEFT);
	file_helptext->SetFont(helptextFont);
	file_helptext->SetForegroundColour(wxColour(100, 100, 100));
	
	custom_key = new wxTextCtrl(panel, wxID_ANY, "custom key", wxPoint(25, 240), wxSize(inputboxsize), wxTE_PASSWORD);
	key_helptext = new wxStaticText(panel, wxID_ANY, "Give your custom key for encrypting", wxPoint(25, 270), wxSize(200, -1), wxALIGN_LEFT);
	key_helptext->SetFont(helptextFont);
	key_helptext->SetForegroundColour(wxColour(100, 100, 100));

	button = new wxButton(panel, wxID_ANY, "SAVE", wxPoint(87, 300), wxSize(75, 40));
}

void MainFrame::BindControls()
{
	button->Bind(wxEVT_BUTTON, &MainFrame::OnSaveButtonClicked, this);
}


void MainFrame::OnSaveButtonClicked(const wxCommandEvent& evt) 
{
	SaveCurrent();
}

void MainFrame::SaveCurrent() 
{	
	//TODO: Ckecking if custom key was added or not and then encoding the initials
	std::string key((custom_key->GetValue()).mb_str());
	blowfish.AddKey(key);

	std::string web((username->GetValue()).mb_str());
	std::string pass((password->GetValue()).mb_str());
	std::string fname((filename->GetValue()).mb_str());
	Initials initials(web, pass, fname);
	std::string message_out = initials.WriteToFile();
	LogMessage(message_out);
}

const void MainFrame::LogMessage(std::string& message) 
{
	wxLogMessage(wxString::FromUTF8(message));
	LogStatus(message);
}

const void MainFrame::LogStatus(std::string& status)
{
	wxLogStatus(wxString::FromUTF8(status));
}
