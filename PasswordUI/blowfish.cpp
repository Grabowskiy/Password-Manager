#include "blowfish.h"


Blowfish::Blowfish() {}

Blowfish::Blowfish(std::string& key)
{
	Blowfish::Initialise(key);
}


void Blowfish::Initialise(std::string& key)
{
	//Initalise P_array
	uint32_t k = 0;
	uint32_t p;
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
