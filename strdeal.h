#ifndef STRDEAL_H
#define STRDEAL_H

#include <string>
#include <QString>
using namespace std;

void str2lowstr(string &str);//将大写字母转换为小写字母，其余不变
void letterFilter(string &str);//过滤非大小写字母并将大写字母转换为小写字母
string QStoStr(const QString &str);//将QString转换为string
QString StrtoQSt(const string &s);//将string转换为QString

#endif // STRDEAL_H
