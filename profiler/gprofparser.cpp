#include <QString>

#include "gprofparser.h"

GprofParser::GprofParser(QString exeName, QString exePath)
{
    functions = new std::vector<Function>();
    this->exeName = exeName;
    this->exePath = exePath;
}

void GprofParser::parseGprofFlatOutput()
{
    QString gprofCommand = "gprof --brief --no-demangle --no-graph " + exeName;

    QString result = executeCommand(gprofCommand, exePath);
    qDebug()<<"------SIZE gprof res: "<<result;
    qDebug()<<"------SIZE gprof res: "<<result.length();

    if( result != "" ){
        QStringList lines = result.split('\n', QString::SkipEmptyParts);
        qDebug()<<"------SIZE gprof: "<<lines.length();
        QString line;
        std::map<QString,QString> symTable = getSymbolTableExecutable();

        if( symTable.size() > 0){
            qDebug()<<"------SIZE ST: "<<symTable.size();
            foreach(line,lines){
                Function f = parseLine(line, symTable);

                if( f.isDefined()){
                    functions->push_back(f);
                }
            }

            for(int i=0; i < functions->size(); i++){
                Function f = functions->at(i);
                qDebug()<<"*****  "<<f.percentage<<"% "<<f.selfSec<<"(self sec) ";
                qDebug()<<f.calls <<"(calls) "<<f.selfSecCall<<"(selfsec call) "<<f.totSecCall<<"(totsec call) "<<f.addr2line;
            }
        }
    }
    int i = 0;

}

/*
 * key: not demangeled function name, value: address
 */
std::map<QString, QString> GprofParser::getSymbolTableExecutable()
{
    QString readelfCommand  = "readelf -Ws " + exeName;
    QString result = executeCommand(readelfCommand, exePath);

    std::map<QString,QString> symTable;
    if(result != ""){
        QStringList lines = result.split('\n',QString::SkipEmptyParts);
        QString line;
        foreach(line, lines){

            QRegExp space("\\s");
            QStringList elems = line.split(space, QString::SkipEmptyParts);

            QRegExp addrRx("[0-9a-fA-F]*");
            QRegExp nameRx(".*");

            if( elems.length() >= 8 && ( addrRx.exactMatch(elems.at(1)) && nameRx.exactMatch(elems.at(7)))){
                symTable[elems.at(7)] = elems.at(1);
            }
        }
    }

    return symTable;
}

/*
 *
 *
 * !!! add verification when converting the float values

    %   cumulative   self              self     total
 time   seconds   seconds    calls   s/call   s/call  name

 float    float     float     uint    float   float

 calls can not be def, hence self s/call and total s/cal may not
 be defined

 */
Function GprofParser::parseLine(QString line, std::map<QString,QString> symTable)
{
    QRegExp space("\\s");
    QStringList elems = line.split(space,QString::SkipEmptyParts);

    QRegExp floatRx("[0-9]*\\.[0-9]{2}");
    QRegExp intRx("[0-9]*");

    if( elems.length() >= 4 && ( floatRx.exactMatch(elems.at(0)) && floatRx.exactMatch(elems.at(1)) && floatRx.exactMatch(elems.at(2))) ){
        if( intRx.exactMatch(elems.at(3)) ){
            if( elems.length() >= 7 && (floatRx.exactMatch(elems.at(4)) && floatRx.exactMatch(elems.at(5)))){
                QString nameFunc = elems.at(6);
                QString addr = symTable.at(nameFunc);
                QString addr2line = getAddrLine(addr);

                // time   seconds   seconds    calls   s/call   s/call  name
                if( addr2line != "")
                    return Function(addr2line,elems.at(0).toFloat(),elems.at(2).toFloat(),elems.at(3).toInt(),elems.at(4).toFloat(), elems.at(5).toFloat());

            }
        }else{
            QString nameFunc = elems.at(3);
            QString addr = symTable.at(nameFunc);
            QString addr2line = getAddrLine(addr);

            return Function(addr2line,elems.at(0).toFloat(),elems.at(2).toFloat());

        }
    }

    return Function();
}

QString GprofParser::getAddrLine(QString addr)
{
    QString addr2lineCommand = "addr2line -a " + addr + " -e " + exeName;
    QString result = executeCommand(addr2lineCommand, exePath);

    if( result != ""){

        QStringList lines= result.split("\n",QString::SkipEmptyParts);
        if( lines.size() >= 2){
            QString line = lines.at(1);

            if( !line.startsWith("??") && line.startsWith("/"))
                return line;
        }
    }

    return QString();
}


