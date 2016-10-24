#include "playfair.h"
#include "strdeal.h"
#include <map>

PlayFair::PlayFair(string key)
{
    char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    keyMap.clear();

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

inline
bool isLowLetter(char ch)//判断是否为小写字母
{
    return ch >= 'a' && ch <= 'z';
}

void CreateMatrixMap(map<char, int> &keyMap, map<char, pair<int, int>> &matrixMap)//根据keyMap创建矩阵关联容器
{
    matrixMap.clear();
    for(auto it = keyMap.begin(); it != keyMap.end(); ++it){
        matrixMap.insert(make_pair(it->first,
                                   make_pair(it->second / (PlayFair::rows - 1), it->second / (PlayFair::cols - 1))));
    }
}

void FairTransfer(char &ch1, char &ch2, map<char, pair<int, int>> &matrixMap)
{
    pair<int, int> pairCh1, pairCh2;
    pairCh1 = matrixMap[ch1];
    pairCh2 = matrixMap[ch2];

}

void PlayFair::encrypt(std::string &clear)
{
    string tmp;

    if(clear.empty())
        return ;

    tmp.reserve(clear.size() * 2);//预分配空间
    str2lowstr(clear);//首先转换为小写字母形式
    map<char, pair<int, int>> matrixMap;
    CreateMatrixMap(keyMap, matrixMap);//构建矩阵关联容器

    for(size_t i = 0; i < clear.size(); ++i){
        char ch = clear.at(i);
        if(!isLowLetter(ch))
            tmp.push_back(ch);//不处理非小写字母
        else{
            char ch2;

            while(++i < clear.size() && !isLowLetter(ch2 = clear.at(i))){
                tmp.push_back(ch2);//如果第一个字母为小写字母，之后的不是小写字母，则不进行处理
            }

            if(i < clear.size()){//当前还有剩余字母
                if(ch2 == ch){//若两字母相同，则赋第二个字母为k，并且使计数字母i减1
                    ch2 = 'k';
                    --i;
                }
            }else{//没有剩余字母，则补充ch2为k
                ch2 = 'k';
            }

            FairTransfer(ch, ch2, matrixMap);

            /* 将两个字符添加进字符串 */
            tmp.push_back(ch);
            tmp.push_back(ch2);
        }
    }
}

void PlayFair::deEncrypt(std::string &cipher)
{
    ;
}
