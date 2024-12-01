#ifndef RSA_H
#define RSA_H

#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include <string>

using namespace boost::multiprecision;


bool IsPrime(cpp_int number);
cpp_int modPow(cpp_int base, cpp_int exp, cpp_int mod);
cpp_int GeneratePrivateKey(cpp_int p, cpp_int q);
cpp_int StringToNumber(const std::string &text);
std::string NumberToString(cpp_int number);
cpp_int EncryptBlock(cpp_int message, cpp_int e, cpp_int n);
cpp_int DecryptBlock(cpp_int cipher, cpp_int d, cpp_int n);
std::vector<cpp_int> EncryptMessage(const std::string &message, cpp_int e, cpp_int n, int blockSize);
std::string DecryptMessage(const std::vector<cpp_int> &encryptedBlocks, cpp_int d, cpp_int n);

#endif // RSA_H
