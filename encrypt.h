#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <string>

struct Encrypt
{
    virtual ~Encrypt(){}

    virtual void encrypt(std::string &clear) = 0;//加密字符串
    virtual void deEncrypt(std::string &cipher) = 0;//解密字符串
};

#endif // ENCRYPT_H
