#ifndef FUNCTION_H
#define FUNCTION_H
#include <QString>
#include <float.h>

class Function
{
public:
    QString addr2line;
    float percentage;
    float selfSec;
    int calls;
    float selfSecCall;
    float totSecCall;

    Function();
    Function(QString addr2line, float percentage, float selfSec, int calls, float selfSecCall,float totSecCall);
    Function(QString addr2line, float percentage, float selfSec);
    bool isDefined();
};

#endif // FUNCTION_H
