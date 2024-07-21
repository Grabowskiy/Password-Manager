#include "MainFrame.h"
#include <wx\wx.h>
#include <memory>

int WIDTH = 600;
int HEIGHT = 300;

#define inputboxsize 200, 30

MainFrame::MainFrame(const std::string& title) : wxFrame(nullptr, wxID_ANY, title) {
	MainFrame::CreateConsol();
	MainFrame::BindControls();
	CreateStatusBar();
}

void MainFrame::CreateConsol() {
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Italic());
	wxFont mainFont(wxFontInfo(wxSize(0, 20)));
	wxFont helptextFont(wxFontInfo(wxSize(0, 12)));

	panel = new wxPanel(this);
	panel->SetBackgroundColour(wxColour(240, 240, 240));
	panel->SetFont(mainFont);

	passwordmanager = new wxStaticText(panel, wxID_ANY, "KEEP IT SAFE", wxPoint(0, 15), 
		wxSize(WIDTH, -1), wxALIGN_CENTER_HORIZONTAL);
	passwordmanager->SetFont(headlineFont);

	username = new wxTextCtrl(panel, wxID_ANY, "username", wxPoint(25, 75), wxSize(inputboxsize));
	password = new wxTextCtrl(panel, wxID_ANY, "password", wxPoint(25, 125), wxSize(inputboxsize));
	filename = new wxTextCtrl(panel, wxID_ANY, "filename.txt", wxPoint(25, 175), wxSize(inputboxsize));
	helptext = new wxStaticText(panel, wxID_ANY, "Give the filename or the path of file", wxPoint(25, 205),
		wxSize(200, -1), wxALIGN_LEFT);
	helptext->SetFont(helptextFont);
	helptext->SetForegroundColour(wxColour(100, 100, 100));
	button = new wxButton(panel, wxID_ANY, "SAVE", wxPoint(87, 230), wxSize(75, 40));
}

void MainFrame::BindControls() {
	button->Bind(wxEVT_BUTTON, &MainFrame::OnSaveButtonClicked, this);
}


void MainFrame::OnSaveButtonClicked(const wxCommandEvent& evt) {
	SaveCurrent();
}

void MainFrame::SaveCurrent() {
	//initials = std::make_shared<Initials>((std::string)(username->GetValue()), 
		//(std::string)(password->GetValue()), (std::string)(filename->GetValue()));
	std::string user((username->GetValue()).mb_str());
	std::string pass((password->GetValue()).mb_str());
	std::string fname((filename->GetValue()).mb_str());
	Initials initials(user, pass, fname);
	std::string message_out = initials.WriteToFile();
	LogMessage(message_out);
}

const void MainFrame::LogMessage(std::string& message) {
	wxLogMessage(wxString::FromUTF8(message));
	LogStatus(message);
}

const void MainFrame::LogStatus(std::string& message) {
	wxLogStatus(wxString::FromUTF8(message));
}



