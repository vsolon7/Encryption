#include <iostream>
#include "AES.h"
#include <string>
#include <random>

int main()
{
	std::string toEncrypt = "My name is Vincent";

	AESEncryption Encryption;

	for(int i = 0; i < 100; i++)
		Encryption.generateKey(AES_128);

	system("pause");
	return 0;
}