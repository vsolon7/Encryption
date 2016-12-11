#pragma once
#include <string>
#include <random>
#include <time.h>
#include <vector>
#include <map>

#define AES_128 128
#define AES_256 256
#define AES_196 196

#define BYTE_SIZE 8 //1 byte is 8 bits
#define OCTAL_SIZE 6 //an octal number is 6 bits

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
		for (int i = 26; i < 52; i++)
		{
			decToB64[i] = (char)(i + 71);
		}
		for (int i = 52; i < 62; i++)
		{
			decToB64[i] = i - 4;
		}
		decToB64[62] = '+';
		decToB64[63] = '/';
	}

	//TODO, right now just XOR's it with a key and returns the binary result
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

	//converts the key to base64
	std::string binaryToBase64(std::vector<bool> intKey)
	{
		std::string base64k = "";

		//total size of the array. I only have to call the .size() function once this way
		int totalKeyBits = intKey.size();

		//keeps track of what bit we left off on
		int track = 0;

		/*
			Basically this converts binary to base 64

			at the end, when theres not enough bytes left to split it to octals, it adds bytes on the end until its divisible by 6

			then it does the exact same thing (converting binary to base64) but the final blank bytes in a 24 bit set become = not A
		*/
		for (int i = 0; (((totalKeyBits-(i)) % 3 == 0) && (i < totalKeyBits)) || (i <= totalKeyBits - OCTAL_SIZE); i += 6)
		{
			std::vector<bool> tempN(OCTAL_SIZE);

			//the next chunk of the binary array into the temp array
			for (int c = i; c < i + OCTAL_SIZE; c++)
				tempN[c-i] = intKey[c];

			int getCharacter = binaryToBaseTen(tempN);

			base64k += decToB64[getCharacter];
			track = i;
		}

		//add empty bytes to the end until there are 3 bytes left
		do
		{
			for (int i = 0; i < BYTE_SIZE; i++)
				intKey.push_back(0);

		} while (((intKey.size() - track)) % OCTAL_SIZE != 0);

		//resets the totalKeyBits size, its bigger now
		totalKeyBits = intKey.size();

		/* do the same thing as above basically, but the end needs to be =s instead of As
		we add an octal_size because this works on the (octet?) after i */
		for (int i = track + OCTAL_SIZE; i < (totalKeyBits); i += OCTAL_SIZE)
		{
			std::vector<bool> tempN(OCTAL_SIZE);

			//the next chunk of the binary array into the temp array
			for (int c = i; c < i + OCTAL_SIZE; c++)
				tempN[c - i] = intKey[c];

			int getCharacter = binaryToBaseTen(tempN);

			//we want the empty octal things that were not part of the original binary to be = not A to distinguish them.
			base64k += ((getCharacter == 0) && (i > (track + OCTAL_SIZE))) ? '=' : decToB64[getCharacter];
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

	//converts base 10 to binary. in probably the WORST way
	std::vector<bool> baseTenToBinary(int n)
	{
		std::vector<bool> binaryByte(BYTE_SIZE);

		//can't be bigger than 255. This stores the values that each place in a binary number is equivalent to in decimal
		int binaryArray[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };

		//each char will only be 1 byte.
		for (int i = 0; i < BYTE_SIZE; i++)
		{
			if (n >= binaryArray[i])
			{
				n -= binaryArray[i];
				binaryByte[i] = 1;
			}
		}
		return binaryByte;
	}

	//converts a string to binary! nice!
	std::vector<bool> stringToBinary(std::string s)
	{
		int sBitSize = s.length() * BYTE_SIZE;
		std::vector<bool> binary(sBitSize);

		int index = 0;

		for (unsigned int i = 0; i < sBitSize; i += 8)
		{

			std::vector<bool> byteTemp(8);
			byteTemp = baseTenToBinary(s[index]);

			for (int j = i; j < i + BYTE_SIZE; j++)
				binary[j] = byteTemp[j - i];

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