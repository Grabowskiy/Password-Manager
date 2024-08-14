#pragma once
#include <string>


static const std::string CharacterSet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.;:()[]{}<>!#$%&'*+-/=?@^_|~\"";

namespace PasswordGenerator
{
	std::string Generate(const size_t& length);
}