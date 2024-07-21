#pragma once

#include <wx\wx.h>
#include "initials.h"
#include <memory>

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
	wxStaticText* helptext;
	wxButton* button;

	//std::shared_ptr<Initials> initials;
private:
	void CreateConsol();
	void BindControls();
	void OnSaveButtonClicked(const wxCommandEvent&);
	void SaveCurrent();
public:
	MainFrame(const std::string&);
	
	const void LogMessage(std::string&);
	const void LogStatus(std::string&);
};