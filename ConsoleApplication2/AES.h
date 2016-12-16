#pragma once
#include <string>
#include <random>
#include <time.h>
#include <vector>
#include <map>
#include "Math.h"

#define AES_128 128
#define AES_256 256
#define AES_196 196

#define BYTE_SIZE 8 //1 byte is 8 bits
#define OCTAL_SIZE 6 //an octal number thing is 6 bits

std::mt19937 randEngine(time(nullptr));
std::uniform_int_distribution<int> generator(0, 1);

class AESEncryption
{
public:
	//TODO, right now just XOR's it with a key and returns the binary result
	std::string XOREncryptDecrypt(std::vector<bool> key, std::string String)
	{
		std::string encryptString;
		std::string tempString;

		std::vector<bool> binStr = stringToBinary(String);
		int size = binStr.size();
		int keySize = key.size();

		std::vector<bool> encrypted(size);

		for (int i = 0; i < size; i++)
		{
			static int j = i;

			encrypted[i] = binStr[i] ^ key[j];

			j++;

			if (j >= (keySize - 1))
				j = 0;

			if (i == size - 1)
				j = 0;
		}

		encryptString = binaryToString(encrypted);
		return encryptString;
	}

	/*
		Generates a key <bits> long

		technically imporperly, as it doesn't start from the smallest binary place
		and go to the biggest, meaning there will always be trailing 0s if the size you want
		is not divisible by 8. May fix later.
	*/
	std::vector<bool> generateKey(int bits)
	{

		//the key is the size in bits, rounded to the nearest byte.
		std::vector<bool> generatedKey(bits + (bits % BYTE_SIZE));

		for (int i = 0; i < bits; i++)
		{
			generatedKey[i] = generator(randEngine); //generate a random 1 or 0
		}

		return generatedKey;
	}
};