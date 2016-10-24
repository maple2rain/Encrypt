#ifndef STRDEAL_H
#define STRDEAL_H

#include <string>
#include <QString>
using namespace std;

void str2lowstr(string &str);
string QStoStr(const QString &str);//将QString转换为string
QString StrtoQSt(const string &s);//将string转换为QString

#endif // STRDEAL_H
