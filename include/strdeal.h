#ifndef STRDEAL_H
#define STRDEAL_H

#include <string>
#include <QString>
#include <vector>
using namespace std;

void str2lowstr(string &str);//将大写字母转换为小写字母，其余不变
void letterFilter(string &str);//过滤非大小写字母并将大写字母转换为小写字母
string QStoStr(const QString &str);//将QString转换为string
QString StrtoQSt(const string &s);//将string转换为QString
bool isLowLetter(char ch);//判断是否为小写字母
void analyzeStr2Num(const string &str, vector<long> &vec); //将字符串中的数字提取出来
void spiltstr(const string &str, const string pattern, vector<string> &vec);//根据模式pattern分割字符串str并存入vector
void str2num(const string str, long &num);
void num2str(const long num, string &str);
#endif // STRDEAL_H
