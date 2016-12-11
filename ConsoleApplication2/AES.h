#pragma once
#include <string>
#include <random>
#include <time.h>
#include <vector>
#include <map>

#define AES_128 128
#define AES_256 256

std::mt19937 randEngine(time(NULL));
std::uniform_int_distribution<int> generator(0, 1);

std::map<int, char> decToB64;

class AESEncryption
{
public:

	//will load the map with all the values of converting numbers to b64
	AESEncryption()
	{
		for (int i = 0; i < 26; i++)
		{
			decToB64[i] = (char)(i + 65);
		}
		for (int i = 26; i < 51; i++)
		{
			decToB64[i] = (char)(i + 71);
		}
		for (int i = 51; i < 62; i++)
		{
			decToB64[i] = i - 4;
		}
		decToB64[62] = '+';
		decToB64[63] = '/';
	}

	//TODO
	std::vector<bool> encrypt(std::vector<bool> key, std::string String)
	{
		std::vector<bool> binStr(String.length() * 8 + 8);
		binStr = stringToBinary(String);

		int size = binStr.size();

		std::vector<bool> encrypted(size);

		for (int i = 0; i < size; i++)
		{
			encrypted[i] = binStr[i] ^ key[i];
		}

		return encrypted;
	}

	//TODO
	std::string decrypt(std::vector<bool> key, std::string String)
	{

	}

	//generates a random key with a certain number of bits
	std::vector<bool> generateKey(int bits)
	{
		std::vector<bool> generatedKey(bits);

		for (int i = 0; i < bits; i++)
		{
			generatedKey[i] = generator(randEngine); //generate a random 1 or 0
		}

		return generatedKey;
	}

	//converts the key to base64
	std::string keyToBase64(std::vector<bool> intKey)
	{
		std::string base64k = "";

		//total size of the array. I only have to call the .size() function once this way
		int totalKeyBits = intKey.size();

		//keeps track of what bit we left off on
		int track = 0;


		/*
			Basically this converts the binary key to base 64

			at the end, when theres less than 1 byte left, it adds a byte on the end until its divisible by 6

			then it does the exact same thing (converting binary to base64) but at the end blank groups of 6 become '=' not 'A'
		*/
		for (int i = 0; ((((totalKeyBits)-i) % 3 == 0) && i < totalKeyBits) || (totalKeyBits - i >= 8); i += 6)
		{
			std::vector<bool> tempN(6);

			tempN[0] = intKey[i];
			tempN[1] = intKey[i + 1];
			tempN[2] = intKey[i + 2];
			tempN[3] = intKey[i + 3];
			tempN[4] = intKey[i + 4];
			tempN[5] = intKey[i + 5];

			int getCharacter = binaryToBaseTen(tempN);

			base64k += decToB64[getCharacter];
			track = i;
		}

		//add empty bytes to the end until it is divisible by 6
		do
		{
			for (int i = 0; i < 8; i++)
				intKey.push_back(0);

		} while (intKey.size() % 6 != 0);

		totalKeyBits = intKey.size();

		//do the same thing as above basically
		for (int i = track + 6; i < (totalKeyBits - 6); i += 6)
		{
			std::vector<bool> tempN(6);

			tempN[0] = intKey[i];
			tempN[1] = intKey[i + 1];
			tempN[2] = intKey[i + 2];
			tempN[3] = intKey[i + 3];
			tempN[4] = intKey[i + 4];
			tempN[5] = intKey[i + 5];

			int getCharacter = binaryToBaseTen(tempN);

			base64k += (getCharacter == 0) ? '=' : decToB64[getCharacter];
		}

		return base64k;
	}

	//Should be fairly simple to understand, if you've ever converted binary by hand this is what that does
	int binaryToBaseTen(std::vector<bool> chunk)
	{
		int sum = 0;

		for (unsigned int c = 0; c < chunk.size(); c++)
		{
			sum += pow(2, c) * chunk[(chunk.size() - 1) - c];
		}

		return sum;
	}

	std::vector<bool> baseTenToBinary(int n)
	{
		std::vector<bool> binaryByte(8);

		//can't be bigger than 256 its just gonna be a char
		int binaryArray[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

		//LOL HOLY FUCK. ill make this better really soon... for now just enjoy the beautiful if statements
		while (n > 0)
		{
			if (n >= binaryArray[0])
			{
				if (n >= binaryArray[1])
				{
					if (n >= binaryArray[2])
					{
						if (n >= binaryArray[3])
						{
							if (n >= binaryArray[4])
							{
								if (n >= binaryArray[5])
								{
									if (n >= binaryArray[6])
									{
										if (n >= binaryArray[7])
										{
											n -= binaryArray[7];
											binaryByte[0] = 1;
										}
										else
										{
											n -= binaryArray[6];
											binaryByte[1] = 1;
										}
									}
									else
									{
										n -= binaryArray[5];
										binaryByte[2] = 1;
									}
								}
								else
								{
									n -= binaryArray[4];
									binaryByte[3] = 1;
								}
							}
							else
							{
								n -= binaryArray[3];
								binaryByte[4] = 1;
							}
						}
						else
						{
							n -= binaryArray[2];
							binaryByte[5] = 1;
						}
					}
					else
					{
						n -= binaryArray[1];
						binaryByte[6] = 1;
					}
				}
				else
				{
					n -= binaryArray[0];
					binaryByte[7] = 1;
				}
			}
			else
			{
				n -= binaryArray[0];
			}
		}

		return binaryByte;
	}

	std::vector<bool> stringToBinary(std::string s)
	{
		int sBitSize = s.length() * 8;
		std::vector<bool> binary(sBitSize);

		int index = 0;

		for (unsigned int i = 0; i < sBitSize - 8; i += 8)
		{

			std::vector<bool> byteTemp(8);
			byteTemp = baseTenToBinary(s[index]);

			for (int j = i; j < i + 8; j++)
			{
				binary[j] = byteTemp[j - i];
			}

			index++;
		}

		return binary;
	}

	//My own power function. Enter the number followed by the power to raise it to
	double pow(int number, int power)
	{
		if (power == 0) //if the power is 0, its always 1
			return 1;

		double total;

		switch (power > 0) //determines if it's positive or negative
		{
		case true: //positive
			total = number;

			for (int c = 1; c < power; c++)
			{
				total *= number;
			}
			break;

		case false: //negative
			total = 1.0 / pow(number, -power); //some nice recursion, divides 1 by the answer of the power with a positive sign
			break;
		}
		return total;
	}
};