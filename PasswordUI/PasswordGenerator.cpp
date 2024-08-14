#include "PasswordGenerator.h"
#include <random>


std::string PasswordGenerator::Generate(const size_t& length)
{
	std::random_device rand;
	std::mt19937_64 gen64(rand());
	std::uniform_int_distribution<> distribution(0, CharacterSet.size() - 1);

	std::string password;
	for (size_t i = 0; i < length; i++)
		password += CharacterSet[distribution(gen64)];
	
	std::random_shuffle(password.begin(), password.end());

	return password;
}
