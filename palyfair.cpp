#include "playfair.h"
#include <map>

PlayFair::PlayFair(string key)
{
    char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    for(int i = 0; i < key.size(); ++i){//创建矩阵首字符串键对
       keyMap.insert(make_pair(key.at(i), keyMap.size()));
    }
    for(int i = 0; i < 26; ++i){//创建剩余键对
        keyMap.insert(make_pair(letters[i], keyMap.size()));
    }

    if(keyMap['z'] < keyMap['y'])
        keyMap['y'] = keyMap['z']; //令z与y的位置相同
    else
        keyMap['z'] = keyMap['y']; //令z与y的位置相同

    /*在控制台输出已创建键对信息*/
    /**/
    qDebug() << "输出键对";
    for(auto it = keyMap.cbegin(); it != keyMap.cend(); ++it){
        qDebug() << it->first << " " << it->second;
    }

    qDebug() << "矩阵赋值并输出对应字符";
    for(int i = 0; i < keyMap.size(); ++i){
        char ch = 'a' + i;
        keyArray[ (int)(keyMap[ch] / 5) ][ keyMap[ch] % 5 ] = ch;
        qDebug() << (int)(keyMap[ch] / 5) << " " << keyMap[ch] % 5;
    }

    qDebug() << "将最后一行和最后一列赋值为与首行和首列相同";
    //虽然两部分可以合并在一个循环体内，因为rows与cols相同，但为了可读性，则用这种方法，并且这种方法仅是增加了i的赋值与判断而已
    for(int i = 0; i < rows; ++i)
        keyArray[i][cols - 1] = keyArray[i][0];
    for(int i = 0; i < cols; ++i)
        keyArray[rows - 1][i] = keyArray[0][i];

    qDebug() << "输出矩阵信息";
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            qDebug() << keyArray[i][j];
}
const std::string& PlayFair::encrypt(const std::string &clear) const
{

    return clear;
}

const std::string& PlayFair::deEncrypt(const std::string &cipher) const
{
    return cipher;
}
