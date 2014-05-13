#ifndef GPROFPARSER_H
#define GPROFPARSER_H

#include "function.h"
#include "helpers.h"

#include <vector>
#include <map>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QDebug>

class GprofParser
{
private:
    std::vector<Function> *functions;
    QString exeName;
    QString exePath;
    std::map<QString,QString> getSymbolTableExecutable();
    Function parseLine(QString line, std::map<QString, QString> symTable);
    QString getAddrLine(QString addr);

public:
    GprofParser(QString exeName, QString exePath);
    void parseGprofFlatOutput();
};

#endif // GPROFPARSER_H
