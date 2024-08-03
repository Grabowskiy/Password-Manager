#include "blowfish.h"
#include <cstdint>
#include <iostream>

Blowfish::Blowfish() {}

void Blowfish::AddKey(std::string& key)
{	
	Blowfish::Initialise(key);
	key_added = true;
}


void Blowfish::Initialise(std::string& key)
{
	//Initalise P_array
	uint32_t k;
	uint32_t p = 0;
	for (size_t i = 0; i < P.size(); i++)
	{
		k = 0x00000000;
		for (size_t j = 0; j < 4; j++)
		{
			k = k << 8 | static_cast<uint8_t>(key[p]);
			p = (p + 1) % key.length();
		}
		P_array[i] = P[i] ^ k;
	}

	// Key expension
	uint32_t left, right;
	left = 0x00000000;
	right = 0x00000000;
	for (size_t i = 0; i < 18; i+=2) 
	{
		Blowfish::Encrypt(left, right);
		P_array[i] = left;
		P_array[i + 1] = right;
	}
		
	S_boxes = S;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 255; j++)
		{
			Blowfish::Encrypt(left, right);
			S_boxes[i][j] = left;
			S_boxes[i][j + 1] = right;
		}
	}
}

uint32_t Blowfish::f_function(uint32_t x)
{
	uint32_t h = S_boxes[0][x >> 24] + S_boxes[1][x >> 16 & 0xff];
	return (h ^ S_boxes[2][x >> 8 & 0xff]) + S_boxes[3][x & 0xff];
}

void Blowfish::Encrypt(uint32_t& left, uint32_t& right)
{	
	for (size_t i = 0; i < rounds; i++)
	{
		left ^= P_array[i];
		right ^= Blowfish::f_function(left);
		std::swap(left, right);
	}
	std::swap(left, right);
	right ^= P_array[16];
	left ^= P_array[17];
}

void Blowfish::Decrypt(uint32_t& left, uint32_t& right)
{
	for (size_t i = rounds + 1; i > 1; i--)
	{
		left ^= P_array[i];
		right ^= Blowfish::f_function(left);
		std::swap(left, right);
	}
	std::swap(left, right);
	right ^= P_array[1];
	left ^= P_array[0];
}

std::string Blowfish::uint_to_string(uint32_t sh) 
{
	std::string str("");
	for (int i = 0; i < 4; i++) 
	{
		str += static_cast<unsigned char>((sh >> i * 8) & 0xFF);
	}
	return str;
}

std::string Blowfish::EncryptPlaintext(std::string plaintext)
{
	if (key_added)
	{
		std::string ciphertext("");

		size_t len = plaintext.length();
		size_t j = sizeof(uint32_t);
		size_t pad = ((len > j * 2) ? (((len / j * 2) + 1) * j * 2 - len) : (j * 2 - len));
		plaintext.append(pad, '\0');
		len = plaintext.length();
		
		std::cout << "My message is: " << plaintext << std::endl;

		uint32_t lt, rt;
		for (size_t i = 0; i < len; i += 8) 
		{
			lt = 0;
			rt = 0;
			lt = *reinterpret_cast<unsigned int*>(const_cast<char*>(plaintext.substr(i, j).c_str()));
			rt = *reinterpret_cast<unsigned int*>(const_cast<char*>(plaintext.substr(i + 4, j).c_str()));
			this->Blowfish::Encrypt(lt, rt);
			ciphertext += Blowfish::uint_to_string(lt) + Blowfish::uint_to_string(rt);
		}

		std::cout << ciphertext << std::endl;

		return ciphertext;
	}
	else
	{
		return "Error: no key added";
	}
	
}

std::string Blowfish::DecryptCiphertext(std::string ciphertext)
{
	if (key_added) 
	{
		std::string plaintext("");

		size_t len = ciphertext.length();
		std::cout << "length: " << len << std::endl;

		uint32_t lt, rt;
		for (size_t i = 0; i < len; i += 8) {
			lt = 0;
			rt = 0;
			lt = *reinterpret_cast<unsigned int*>(const_cast<char*>(ciphertext.substr(i, 4).c_str()));
			rt = *reinterpret_cast<unsigned int*>(const_cast<char*>(ciphertext.substr(i + 4, 4).c_str()));
			this->Blowfish::Decrypt(lt, rt);
			plaintext += Blowfish::uint_to_string(lt) + Blowfish::uint_to_string(rt);
		}

		std::cout << plaintext << std::endl;

		return plaintext;
	}
	else
	{
		return "Error: no key added";
	}
}
