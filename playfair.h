#ifndef PLAYFIAR_H
#define PLAYFIAR_H

#include <QDebug>
#include <string>
#include <map>
#include "encrypt.h"

using namespace std;

class PlayFair : public Encrypt{
public:
    PlayFair(string key = "");//形参为密钥
    ~PlayFair(){}
    
    void encrypt(std::string &clear);//加密算法
    void deEncrypt(std::string &cipher);//解密算法

    inline
    char getKey(const int rows, const int cols) const//获取rows行cols列值
    {
        if(rows < 1 || rows > PlayFair::rows
            || cols < 1 || cols > PlayFair::cols)
            return '\0';

        return keyArray[rows - 1][cols - 1];
    }

    inline
    int getKeyValue(char key) const//获取关键字key的值
    {
        auto it = keyMap.find(key);
        if(it != keyMap.end())
            return it->second;

        return -1;
    }

private:
    void FairTransfer(char &ch1, char &ch2, map<char, pair<int, int>> &matrixMap);//playfair字符转换
    void FairReturn(char &ch1, char &ch2, map<char, pair<int, int>> &matrixMap);//playfair字符回退

   public:
    static const int rows = 6;
    static const int cols = 6;
private:
    char keyArray[rows][cols];
    map<char, int> keyMap;
};




#endif // PLAYFIAR_H
