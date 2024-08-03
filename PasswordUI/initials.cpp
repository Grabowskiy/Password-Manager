#include "initials.h"

#include <iostream>


const bool Initials::CheckFilenameValidity(std::string& name) {
	std::string subname = name.substr(name.size() - 4, name.size());
	if (subname == ".txt") 
		return true;
	else 
		return false;
};

Initials::Initials() {};

Initials::Initials(std::string username_in, std::string password_in, std::string filename_in)
		: website(username_in), password(password_in), filename(filename_in) {};

Initials::~Initials() {};

std::string Initials::GetWebsite() const { return website; };

std::string Initials::GetPassword() const { return password; };

std::string Initials::GetFilename() const { return filename; };

void Initials::SetWebsite(std::string new_username) {
	website = new_username;
};

void Initials::SetPassword(std::string new_password) {
	password = new_password;
};

void Initials::SetPath(std::string new_filename) {
	filename = new_filename;
};

std::string Initials::WriteToFile() {

	const bool valid = Initials::CheckFilenameValidity(filename);
	if (valid) 
	{
		file.open(filename, std::fstream::out | std::fstream::app);
		if (file.is_open()) 
		{
			file << website << std::endl;
			file << password << std::endl;
			file << "------------" << std::endl;

			file.close();
			message = "Encrypted data written to the file successfully.";
		}
		else
			message = "Failed to open initials file.";
		}
	else
		message = "Invalid filename, must end with '.txt'";
	return message;
};
