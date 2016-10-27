#ifndef HILL_H
#define HILL_H

#include "encrypt.h"
#include <string>

using namespace std;

class HillEnc : public Encrypt{

public:
    enum IsValid{
        INVALID, VALID
    };

    HillEnc(string key = "rrfvsvcct", IsValid isvalid = INVALID);//默认矩阵字符
    //HillEnc(string key = "aacbcadea", IsValid isvalid = INVALID);//默认矩阵字符
    ~HillEnc(){}

    void encrypt(std::string &clear);//加密算法
    void deEncrypt(std::string &cipher);//解密算法

    char getKey(const size_t rows, const size_t cols) const//获取rows行cols列值
    {
        if(rows < 1 || rows > HillEnc::rows
            || cols < 1 || cols > HillEnc::cols)
            return '\0';

        return keyArray[rows - 1][cols - 1];
    }

    char getRekey(const size_t rows, const size_t cols) const//获取rows行cols列值
    {
        if(rows < 1 || rows > HillEnc::rows
            || cols < 1 || cols > HillEnc::cols)
            return '\0';

        return reKeyArray[rows - 1][cols - 1];
    }

    bool available(){
        return valid == VALID;
    }

private:
    void HillTransfer(string &clear);//hill字符串转换
    void HillReturn(string &cipher);//hill字符串回退
public:
    static const size_t rows = 3;
    static const size_t cols = 3;

private:
    IsValid valid;
    double keyArray[rows][cols];
    double reKeyArray[rows][cols];
};

#endif // HILL_H
