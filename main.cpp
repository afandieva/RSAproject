#include "rsa.h"
#include <iostream>
#include <string>

int main() {
    cpp_int p = 489133282872437279;
    cpp_int q = 4398042316799;

    cpp_int d = GeneratePrivateKey(p, q);
    cpp_int e = 65537;
    cpp_int n = p * q;

    std::string message;
    std::cout << "Введите сообщение для шифрования: ";
    std::cin >> message;

    int blockSize = message.size();
    std::vector<cpp_int> encryptedMessage = EncryptMessage(message, e, n, blockSize);

    std::cout << "Зашифрованное сообщение: ";
    for (const auto &block : encryptedMessage) {
        std::cout << block << " ";
    }
    std::cout << std::endl;

    std::string decryptedMessage = DecryptMessage(encryptedMessage, d, n);
    std::cout << "Расшифрованное сообщение: " << decryptedMessage << std::endl;

    return 0;
}
