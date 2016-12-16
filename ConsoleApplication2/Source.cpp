#include <iostream>
#include "AES.h"
#include <string>
#include <random>
#include <fstream>
#include "Math.h"

int main()
{
	std::fstream fileEncrypt;

	fileEncrypt.open("C:\\Users\\Vsolon7\\Documents\\C++\\TestEncryption.txt", std::ios::in);

	std::string toEncrypt;
	std::string line;

	if (fileEncrypt.is_open())
	{
		while (std::getline(fileEncrypt, line))
		{
			toEncrypt += line;
			
			if(!fileEncrypt.eof())
				toEncrypt += "\n";
		}
	}

	fileEncrypt.close();

	AESEncryption Encryption;

	std::vector<bool> key = Encryption.generateKey(AES_128);
	std::string encryptedBinary = Encryption.XOREncryptDecrypt(key, toEncrypt);


	std::vector<bool> stringBinary = stringToBinary(toEncrypt);


	std::cout << "Key (base64): " << binaryToBase64(key) << "\n\n";
	std::cout << "Message: " << toEncrypt << "\n\n";
	std::cout << "Message (base 64): " << binaryToBase64(stringToBinary(toEncrypt)) << "\n\n";

	std::cout << "Encrypted String (base64): ";
	std::cout << binaryToBase64(stringToBinary(encryptedBinary));
	std::cout << "\n\nDecrypted: ";
	std::cout << Encryption.XOREncryptDecrypt(key, encryptedBinary);

	fileEncrypt.open("C:\\Users\\Vsolon7\\Documents\\C++\\Encryption result.txt");
	fileEncrypt << binaryToBase64(stringToBinary(encryptedBinary)) << "\n\nKEY: " << binaryToBase64(key);

	std::cout << "\n\n";

	system("pause");
	return 0;
}