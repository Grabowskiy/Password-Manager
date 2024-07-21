#pragma once

#include <iostream>
#include <string>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <fstream>


class Initials
{
private:
	std::string username;
	std::string password;
	std::string filename = "initials.txt";
	std::ofstream file;
	std::string message;
private:
	const bool CheckFilenameValidity(std::string& name){
		std::string subname = name.substr(name.size() - 4, name.size());
		if (subname == ".txt") return true;
		else return false;
	};

public:
	Initials() {};

	Initials(std::string username_in, std::string password_in, std::string filename_in)
		: username(username_in), password(password_in), filename(filename_in) {};

	~Initials() {};

	std::string GetUser() const { return username; };

	std::string GetPassword() const { return password; };

	std::string GetFilename() const { return filename; };

	void SetUser(std::string new_username) {
		username = new_username;
	};

	void SetPassword(std::string new_password) {
		password = new_password;
	};

	void SetPath(std::string new_filename) {
		filename = new_filename;
	};

	std::string WriteToFile(){

		const bool valid = CheckFilenameValidity(filename);
		if (valid) {
			file.open(filename, std::fstream::out | std::fstream::app);
			if (file.is_open()) {
				file << username << std::endl;
				file << password << std::endl;
				file << filename << std::endl;

				file.close();
				message = "Initials written to the file successfully.";
			}
			else
				message = "Failed to open initials file.";
		}
		else
			message = "Invalid filename, must end with '.txt'";
		return message;
	};
};
