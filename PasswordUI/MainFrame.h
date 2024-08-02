#pragma once

#include <wx\wx.h>
#include "initials.h"
#include "blowfish.h"

extern int WIDTH;
extern int HEIGHT;

class MainFrame : public wxFrame
{
private:
	wxPanel* panel;
	wxStaticText* passwordmanager;
	wxTextCtrl* username;
	wxTextCtrl* password;
	wxTextCtrl* filename;
	wxStaticText* file_helptext;
	wxButton* button;
	wxTextCtrl* custom_key;
	wxStaticText* key_helptext;


	Blowfish blowfish;

private:
	void CreateConsol();
	void BindControls();
	void OnSaveButtonClicked(const wxCommandEvent& evt);
	void SaveCurrent();

public:
	MainFrame(const std::string& title);
	
	const void LogMessage(std::string& message);
	const void LogStatus(std::string& status);
};