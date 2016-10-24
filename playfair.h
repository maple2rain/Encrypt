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
    
    const std::string &encrypt(const std::string &clear) const;
    const std::string &deEncrypt(const std::string &cipher) const;

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
public:
    static const int rows = 6;
    static const int cols = 6;
private:
    char keyArray[rows][cols];
    map<char, int> keyMap;
};

#endif // PLAYFIAR_H
