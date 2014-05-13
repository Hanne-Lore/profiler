#include "helpers.h"
#include <cstdio>
#include <QDebug>

QString executeCommand(QString cmd, QString dir){

    qDebug()<<"helpers command: "<<cmd;
    QString cd("cd " + dir +" && ");
    QString fin = cd + cmd;
    qDebug()<<"helpers final command: "<<fin;

    FILE* pipe = popen(fin.toStdString().c_str(), "r");
    if (!pipe)
        return "error";
    char buffer[512];

    std::string result = "";

    while(!feof(pipe)) {
        memset(buffer,0,512);
        if(fread(buffer,1,511,pipe) != 0)
            result += buffer;
    }
    pclose(pipe);

    QString t = QString::fromStdString(result);

    QStringList l = t.split('\n');
    qDebug()<<"HELPERS SIZE: "<<l.size();

    return t;

}

