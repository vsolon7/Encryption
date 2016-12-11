#include <iostream>
#include "AES.h"
#include <string>
#include <random>

int main()
{
	std::string toEncrypt = "My name is Vince";
	//std::string encrypted;

	AESEncryption Encryption;

	std::vector<bool> key = Encryption.generateKey(196);
	std::vector<bool> encryptedBinary = Encryption.encrypt(key, toEncrypt);
	std::vector<bool> stringBinary = Encryption.stringToBinary(toEncrypt);

	

	std::cout << "Key: " << Encryption.binaryToBase64(key) << "\n\n";
	std::cout << "Message: " << toEncrypt << "\n\n";

	for (int i = 0; i < stringBinary.size(); i++)
	{
		std::cout << stringBinary[i];

		if ((i + 1) % 8 == 0)
			std::cout << " ";
	}

	std::cout << "\n\nEncryptedBinaryString: \n\n";

	for (int i = 0; i < encryptedBinary.size(); i++)
	{
		std::cout << encryptedBinary[i];

		if ((i + 1) % 8 == 0)
			std::cout << " ";
	}

	std::cout << "\n\n";

	system("pause");
	return 0;
}