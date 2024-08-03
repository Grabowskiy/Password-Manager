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
	wxButton* save_button;
	wxTextCtrl* custom_key;
	wxStaticText* key_helptext;
	
	wxTextCtrl* decrypt_filename;
	wxStaticText* decrypt_helptext;
	wxTextCtrl* decrypt_key;
	wxStaticText* dkey_helptext;
	wxButton* decrypt_button;

	Blowfish blowfish;
	bool blowfish_already_initialised = false;

private:
	void CreateConsol();
	void BindControls();
	void OnSaveButtonClicked(const wxCommandEvent& evt);
	void OnDecryptButtonClicked(const wxCommandEvent& evt);
	void SaveCurrent();

public:
	MainFrame(const std::string& title);
	
	const void LogMessage(std::string& message);
	const void LogStatus(std::string& status);

	std::string DecryptMyFile(std::string& filepath, std::string& key);
};