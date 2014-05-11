#include "helpers.h"
#include <cstdio>
#include <QDebug>

QString executeCommand(QString cmd){

    qDebug()<<cmd;

    FILE* pipe = popen(cmd.toStdString().c_str(), "r");
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
    //qDebug()<<t;

    return t;

}

