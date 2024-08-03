#pragma once

#include <string>
#include <fstream>

class Initials
{
private:
	std::string website;
	std::string password;
	std::string filename = "initials.txt";
	std::ofstream file;
	std::string message;
public:
	Initials();

	Initials(std::string username_in, std::string password_in, std::string filename_in);
	
	~Initials();

	std::string GetWebsite() const;

	std::string GetPassword() const;

	std::string GetFilename() const;

	void SetWebsite(std::string new_username);

	void SetPassword(std::string new_password);

	void SetPath(std::string new_filename);

	const bool CheckFilenameValidity(std::string& name);

	std::string WriteToFile();
};
