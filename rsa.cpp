#include "rsa.h"
#include <iostream>

// Проверка, является ли число простым
bool IsPrime(cpp_int number) {
    if (number <= 1) {
        return false;
    }
    for (cpp_int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

// Быстрое возведение в степень по модулю
cpp_int modPow(cpp_int base, cpp_int exp, cpp_int mod) {
    cpp_int result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Генерация закрытого ключа
cpp_int GeneratePrivateKey(cpp_int p, cpp_int q) {
    if (!IsPrime(p) || !IsPrime(q)) {
        std::cerr << "Error: One or both numbers are not prime.\n";
        return 0;
    }

    cpp_int phi = (p - 1) * (q - 1);
    cpp_int e = 65537; // Фиксированная открытая экспонента
    cpp_int d = 0;
    cpp_int k = 1;

    while (true) {
        if ((k * phi + 1) % e == 0) {
            d = (k * phi + 1) / e;
            break;
        }
        ++k;
    }
    return d;
}

// Преобразование текста в число
cpp_int StringToNumber(const std::string &text) {
    cpp_int number = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        number = number * 256 + static_cast<unsigned char>(text[i]);
    }
    return number;
}

// Преобразование числа в текст
std::string NumberToString(cpp_int number) {
    std::string text;
    while (number > 0) {
        text.insert(text.begin(), static_cast<char>(number % 256));
        number /= 256;
    }
    return text;
}

// Шифрование блока
cpp_int EncryptBlock(cpp_int message, cpp_int e, cpp_int n) {
    return modPow(message, e, n);
}

// Расшифровка блока
cpp_int DecryptBlock(cpp_int cipher, cpp_int d, cpp_int n) {
    return modPow(cipher, d, n);
}

// Шифрование сообщения по блокам
std::vector<cpp_int> EncryptMessage(const std::string &message, cpp_int e, cpp_int n, int blockSize) {
    std::vector<cpp_int> encryptedBlocks;
    for (size_t i = 0; i < message.size(); i += blockSize) {
        std::string block = message.substr(i, blockSize);
        cpp_int blockNumber = StringToNumber(block);
        encryptedBlocks.push_back(EncryptBlock(blockNumber, e, n));
    }
    return encryptedBlocks;
}

// Расшифровка сообщения из блоков
std::string DecryptMessage(const std::vector<cpp_int> &encryptedBlocks, cpp_int d, cpp_int n) {
    std::string decryptedMessage;
    for (const cpp_int &cipherBlock : encryptedBlocks) {
        cpp_int decryptedBlock = DecryptBlock(cipherBlock, d, n);
        decryptedMessage += NumberToString(decryptedBlock);
    }
    return decryptedMessage;
}
