#include "function.h"

Function::Function()
{

}

Function::Function(QString addr2line, float percentage, float selfSec, int calls, float selfSecCall, float totSecCall)
{
    this->addr2line = addr2line;
    this->percentage = percentage;
    this->selfSec = selfSec;
    this->calls = calls;
    this->selfSecCall = selfSecCall;
    this->totSecCall = totSecCall;
}

Function::Function(QString addr2line, float percentage, float selfSec)
{
    this->addr2line = addr2line;
    this->percentage = percentage;
    this->selfSec = selfSec;
}

bool Function::isDefined()
{
    return !addr2line.isNull();
}
