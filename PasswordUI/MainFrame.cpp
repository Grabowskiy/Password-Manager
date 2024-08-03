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
	
	custom_key = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(25, 240), wxSize(inputboxsize), wxTE_PASSWORD);
	key_helptext = new wxStaticText(panel, wxID_ANY, "Give your custom key for encrypting", wxPoint(25, 270), wxSize(200, -1), wxALIGN_LEFT);
	key_helptext->SetFont(helptextFont);
	key_helptext->SetForegroundColour(wxColour(100, 100, 100));

	save_button = new wxButton(panel, wxID_ANY, "SAVE", wxPoint(87, 300), wxSize(75, 40));

	decrypt_filename = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(312, 75), wxSize(inputboxsize));
	decrypt_helptext = new wxStaticText(panel, wxID_ANY, "Give filepath to decryprt", wxPoint(312, 105), wxSize(200, -1), wxALIGN_LEFT);
	decrypt_helptext->SetFont(helptextFont);
	decrypt_helptext->SetForegroundColour(wxColour(100, 100, 100));

	decrypt_key = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(312, 140), wxSize(inputboxsize), wxTE_PASSWORD);
	dkey_helptext = new wxStaticText(panel, wxID_ANY, "Give your custom key for decrypting", wxPoint(312, 170), wxSize(200, -1), wxALIGN_LEFT);
	dkey_helptext->SetFont(helptextFont);
	dkey_helptext->SetForegroundColour(wxColour(100, 100, 100));
	
	decrypt_button = new wxButton(panel, wxID_ANY, "DECRYPT", wxPoint(351, 200), wxSize(120, 40));
}

void MainFrame::BindControls()
{
	save_button->Bind(wxEVT_BUTTON, &MainFrame::OnSaveButtonClicked, this);
	decrypt_button->Bind(wxEVT_BUTTON, &MainFrame::OnDecryptButtonClicked, this);
}


void MainFrame::OnSaveButtonClicked(const wxCommandEvent& evt) 
{
	SaveCurrent();
}

void MainFrame::SaveCurrent()
{
	std::string key((custom_key->GetValue()).mb_str());

	if (key.length() > 6)
	{
		if (!blowfish_already_initialised)
		{
			blowfish.AddKey(key);
			blowfish_already_initialised = true;
		}
		std::string web((username->GetValue()).mb_str());
		std::string pass((password->GetValue()).mb_str());
		std::string fname((filename->GetValue()).mb_str());

		std::string web_encrypted = blowfish.EncryptPlaintext(web);
		std::string pass_encrypted = blowfish.EncryptPlaintext(pass);

		Initials initials(web_encrypted, pass_encrypted, fname);
		std::string message_out = initials.WriteToFile();
		LogMessage(message_out);
	}

	else
	{
		std::string error_message = "Key is invalid, it must be at least 6 characters.";
		LogMessage(error_message);
	}	
}

void MainFrame::OnDecryptButtonClicked(const wxCommandEvent& evt)
{
	std::string message = "";

	std::string fname((decrypt_filename->GetValue()).mb_str());
	std::string d_key((decrypt_key->GetValue()).mb_str());

	if ((fname.substr(fname.size() - 4, fname.size())) == ".txt")
	{
		message = DecryptMyFile(fname, d_key);
	}
	else
	{
		message = "Invalid file, must end with '.txt'.";
	}
	
	LogMessage(message);
}

std::string MainFrame::DecryptMyFile(std::string& filepath, std::string& key)
{
	std::string to_return = "";

	std::ifstream file;
	file.open(filepath, std::fstream::in);

	if (key.length() < 6)
		return "Invalid decryption key, it must be at least 6 characters.";

	if (!blowfish_already_initialised)
	{
		blowfish.AddKey(key);
		blowfish_already_initialised = true;
	}

	if (file.is_open())
	{
		std::string row = "";
		while (std::getline(file, row))
		{
			if (row != "------------")
			{
				std::string decrypted_row = blowfish.DecryptCiphertext(row);
				to_return.append(decrypted_row + "\n");
			}
			else
				to_return.append("------------\n");
		}
		file.close();
		std::ofstream file_out;
		file_out.open(filepath, std::ofstream::out | std::ofstream::app);
		file_out << to_return << std::endl;
		file_out.close();
		return to_return;
	}
	else
		return "Could not open file.";
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
