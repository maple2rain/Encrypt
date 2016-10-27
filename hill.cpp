#include "hill.h"
#include "strdeal.h"
#include "matrix.h"
#include "strdeal.h"
#include <QDebug>

HillEnc::HillEnc(string key, IsValid isvalid) :
    valid(isvalid)
{
    letterFilter(key);//过滤无效字符

    if(key.size() != (rows * cols)) return ;
    auto it = key.begin();

    for(size_t i = 0; i != rows; ++i){
        for(size_t j = 0; j != cols; ++j){
            keyArray[i][j] = *it++ - 'a';//创建矩阵
        }
    }

    if(false == CreateInvMatrix(keyArray, reKeyArray))
        valid = INVALID;
    else
        valid = VALID;

    for(size_t i = 0; i != rows; ++i)
        for(size_t j = 0; j != rows; ++j){
            if(reKeyArray[i][j] > 0)
                reKeyArray[i][j] = (long)(reKeyArray[i][j] + 0.5) %  26;//c++向0取整
            else if(reKeyArray[i][j] < -0.5)
                reKeyArray[i][j] = 26 + (long)(reKeyArray[i][j] - 0.5) % 26;
            else
                reKeyArray[i][j] = 0;
        }
//    string reKey = "ejpprgyar";

//    auto it2 = reKey.begin();

//    for(size_t i = 0; i != rows; ++i){
//        for(size_t j = 0; j != cols; ++j){
//            reKeyArray[i][j] = *it2++ - 'a';//创建矩阵
//        }
//    }

}

void HillEnc::encrypt(string &clear){
    string tmp;

    if(clear.empty())
        return ;

    tmp.reserve(clear.size() + 2);//预分配空间
    str2lowstr(clear);//首先转换为小写字母形式

    for(size_t i = 0; i < clear.size(); ++i){
        char ch = clear.at(i);

        if(!isLowLetter(ch))
            tmp.push_back(ch);//不处理非小写字母
        else{
            string norLetter1 = "";
            string norLetter2 = "";
            char ch2, ch3;

            while(++i < clear.size() && !isLowLetter(ch2 = clear.at(i))){
                norLetter1.push_back(ch2);//如果第一个字母为小写字母，之后的不是小写字母，则不进行处理
            }

            if(i < clear.size()){//当前还有剩余字母
                while(++i < clear.size() && !isLowLetter(ch3 = clear.at(i))){
                    norLetter2.push_back(ch3);//如果第一个字母为小写字母，之后的不是小写字母，则不进行处理
                }
                if(i >= clear.size())
                    ch3 = 'x';

            }else{//没有剩余字母，则补充x
                ch2 = ch3 = 'x';
            }

            string trans = {ch, ch2, ch3};
            this->HillTransfer(trans);//转换字符

            /* 将两个字符和非字母字符串添加进字符串 */
            tmp.push_back(trans[0]);
            tmp += norLetter1;
            tmp.push_back(trans[1]);
            tmp += norLetter2;
            tmp.push_back(trans[2]);
        }
    }

    clear.swap(tmp);
}

void HillEnc::deEncrypt(string &cipher)
{
    string tmp;

    if(cipher.empty())
        return ;

    tmp.reserve(cipher.size());//预分配空间
    str2lowstr(cipher);//首先转换为小写字母形式

    for(size_t i = 0; i < cipher.size(); ++i){
        char ch = cipher.at(i);

        if(!isLowLetter(ch))
            tmp.push_back(ch);//不处理非小写字母
        else{
            string norLetter1 = "";
            string norLetter2 = "";
            char ch2, ch3;

            while(++i < cipher.size() && !isLowLetter(ch2 = cipher.at(i))){
                norLetter1.push_back(ch2);//如果第一个字母为小写字母，之后的不是小写字母，则不进行处理
            }

            if(i < cipher.size()){//当前还有剩余字母
                while(++i < cipher.size() && !isLowLetter(ch3 = cipher.at(i))){
                    norLetter2.push_back(ch3);//如果第一个字母为小写字母，之后的不是小写字母，则不进行处理
                }
                if(i >= cipher.size())
                    ch3 = 'x';

            }else{//没有剩余字母，则补充x
                ch2 = ch3 = 'x';
            }

            string trans = {ch, ch2, ch3};
            this->HillReturn(trans);//转换字符

            /* 将两个字符和非字母字符串添加进字符串 */
            tmp.push_back(trans[0]);
            tmp += norLetter1;
            tmp.push_back(trans[1]);
            tmp += norLetter2;
            tmp.push_back(trans[2]);
        }
    }

    cipher.swap(tmp);
}

void HillEnc::HillTransfer(string &clear)
{
    string tmp;
    for(size_t i = 0; i != rows; ++i)
        clear[i] -= 'a';
    for(size_t i = 0; i != rows; ++i){
        int c = 0;
        for(size_t j = 0; j != cols; ++j){
            c += clear[j] * keyArray[i][j];
        }
        tmp.push_back(c % 26 + 'a');
    }
    clear.swap(tmp);
}

void HillEnc::HillReturn(string &cipher)
{
    string tmp;
    for(size_t i = 0; i != rows; ++i)
        cipher[i] -= 'a';
    for(size_t i = 0; i != rows; ++i){
        int c = 0;
        for(size_t j = 0; j != cols; ++j){
            c += cipher[j] * reKeyArray[i][j];
        }
        tmp.push_back(c % 26 + 'a');
    }
    cipher.swap(tmp);
}
