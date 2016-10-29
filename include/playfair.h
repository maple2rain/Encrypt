#ifndef PLAYFIAR_H
#define PLAYFIAR_H

#include <QDebug>
#include <string>
#include <map>
#include "encrypt.h"

using namespace std;

class PlayFair : public Encrypt{
public:
    PlayFair(string key = "");//�β�Ϊ��Կ
    ~PlayFair(){}
    
    void encrypt(std::string &clear);//�����㷨
    void deEncrypt(std::string &cipher);//�����㷨

    inline
    char getKey(const size_t rows, const size_t cols) const//��ȡrows��cols��ֵ
    {
        if(rows < 1 || rows > PlayFair::rows
            || cols < 1 || cols > PlayFair::cols)
            return '\0';

        return keyArray[rows - 1][cols - 1];
    }

    inline
    size_t getKeyValue(char key) const//��ȡ�ؼ���key��ֵ
    {
        auto it = keyMap.find(key);
        if(it != keyMap.end())
            return it->second;

        return -1;
    }

private:
    void FairTransfer(char &ch1, char &ch2, map<char, pair<size_t, size_t> > &matrixMap);//playfair�ַ�ת��
    void FairReturn(char &ch1, char &ch2, map<char, pair<size_t, size_t>> &matrixMap);//playfair�ַ�����

   public:
    static const size_t rows = 6;
    static const size_t cols = 6;
private:
    char keyArray[rows][cols];
    map<char, size_t> keyMap;
};

#endif // PLAYFIAR_H
