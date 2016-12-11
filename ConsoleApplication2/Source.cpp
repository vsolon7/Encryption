#include <iostream>
#include "AES.h"
#include <string>
#include <random>
#include "Math.h"

int main()
{
	std::string toEncrypt = "My name is c";
	//std::string encrypted;

	AESEncryption Encryption;

	std::vector<bool> key = Encryption.generateKey(AES_128);
	std::vector<bool> encryptedBinary = Encryption.encrypt(key, toEncrypt);
	std::vector<bool> stringBinary = stringToBinary(toEncrypt);



	std::cout << "Key: " << binaryToBase64(key) << "\n\n";
	std::cout << "Message: " << toEncrypt << "\n\n";

	std::cout << "Encrypted String: ";

	std::cout << binaryToBase64(encryptedBinary);

	std::cout << "\n\nDecrypted: ";

	std::cout << Encryption.decrypt(key, binaryToString(encryptedBinary));

	std::cout << "\n\n";

	system("pause");
	return 0;
}