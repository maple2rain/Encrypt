#include "../include/strdeal.h"
#include <sstream>

void str2lowstr(string &str)
{
    string tmp;
    tmp.reserve(str.size());

    for(size_t i = 0; i < str.size(); ++i){
        char ch = str.at(i);
        if(ch >= 'A' && ch <= 'Z')
            tmp.push_back(ch + ('a' - 'A'));
        else
            tmp.push_back(ch);
    }

    str.swap(tmp);
}

void letterFilter(string &str)
{
    string tmp;
    tmp.reserve(str.size());

    for(size_t i = 0; i < str.size(); ++i){
        char ch = str.at(i);
        if(ch >= 'a' && ch <= 'z')
            tmp.push_back(ch);
        else if(ch >= 'A' && ch <= 'Z')
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

bool isLowLetter(char ch)//判断是否为小写字母
{
    return ch >= 'a' && ch <= 'z';
}

void analyzeStr2Num(const string &str, vector<long> &vec)
{
    vector<string> strvec;
    spiltstr(str, ",", strvec);

    if(!strvec.empty()){
        for(int i = 0; i < strvec.size(); ++i){
            istringstream stream;
            stream.str(strvec[i]);
            long num;
            stream >> num;
            vec.push_back(num);
        }
    }
}

void spiltstr(const string &str, const string pattern, vector<string> &vec)
{
    int i;
    for(i = 0; i < str.size(); ++i){
        string::size_type pos;
        pos = str.find(pattern, i); //find the pos of pattern

        if(pos < str.size()){
            string s = str.substr(i, pos - i);  //copy the substr
            vec.push_back(s);   //add substr
            i = pos + pattern.size() - 1;
        }else{
            break;
        }
    }

    string s = str.substr(i, str.size() - i);
    vec.push_back(s);
}

void str2num(const string str, long &num)
{
    istringstream is;
    is.str(str);
    is >> num;
}

void num2str(const long num, string &str)
{
    ostringstream os;
    os << num;
    str = os.str();
}
