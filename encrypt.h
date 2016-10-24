#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <string>

struct Encrypt
{
    virtual ~Encrypt(){}

    virtual const std::string &encrypt(const std::string &clear) const = 0;//加密字符串
    virtual const std::string &deEncrypt(const std::string &cipher) const = 0;//解密字符串
};

#endif // ENCRYPT_H
