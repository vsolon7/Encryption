#include <iostream>
#include "AES.h"
#include <string>
#include <random>

int main()
{
	std::string toEncrypt = "My name is Vinc";
	//std::string encrypted;

	AESEncryption Encryption;

	std::vector<bool> key = Encryption.generateKey(AES_128);
	std::vector<bool> binaryString = Encryption.stringToBinary(toEncrypt);
	std::vector<bool> encryptedBinary = Encryption.encrypt(key, toEncrypt);

	

	std::cout << "\n\nKey: " << Encryption.keyToBase64(key) << "\n\n";
	std::cout << "Message: " << toEncrypt << "\n\n";

	std::cout << "Binary: ";

	for (int i = 0; i < binaryString.size(); i++)
	{
		std::cout << binaryString[i];

		if ((i + 1) % 8 == 0)
			std::cout << " ";
	}

	std::cout << "\n\nEncryptedBinary: ";

	for (int i = 0; i < encryptedBinary.size(); i++)
	{
		std::cout << encryptedBinary[i];

		if ((i + 1) % 8 == 0)
			std::cout << " ";
	}

	system("pause");
	return 0;
}