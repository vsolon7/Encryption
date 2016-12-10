#include <iostream>
#include "AES.h"
#include <string>
#include <random>

int main()
{
	std::string toEncrypt = "My name is Vincent";

	AESEncryption Encryption;

	for(int i = 1; i <= 100; i++)
		std::cout << i << ".) "<< Encryption.keyToBase64(Encryption.generateKey(AES_128)) << "\n";

	system("pause");
	return 0;
}