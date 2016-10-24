#include "strdeal.h"

void str2lowstr(string &str)
{
    string tmp;
    tmp.reserve(str.size());

    for(size_t i = 0; i < str.size(); ++i){
        char ch = str.at(i);
        if(ch >= 'a' && ch <= 'z')
            tmp.push_back(ch);
        if(ch >= 'A' && ch <= 'Z')
            tmp.push_back(ch + ('a' - 'A'));
    }

    str.swap(tmp);
}

string QStoStr(const QString &str)//将QString转换为string
{
    return string((const char*)str.toLocal8Bit());
}

QString StrtoQSt(const string &s)//将string转换为QString
{

   return QString(QString::fromLocal8Bit(s.c_str()));
}
