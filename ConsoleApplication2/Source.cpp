#include <iostream>
#include "AES.h"
#include <string>
#include <random>

int main()
{
	std::string toEncrypt = "My name is Vince";
	//std::string encrypted;

	AESEncryption Encryption;

	std::vector<bool> key = Encryption.generateKey(AES_128);
	std::vector<bool> encryptedBinary = Encryption.encrypt(key, toEncrypt);

	

	std::cout << "Key: " << Encryption.binaryToBase64(key) << "\n\n";
	std::cout << "Message: " << toEncrypt << "\n\n";

	std::cout << "EncryptedBinaryString: \n\n";

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