#include "Parameters.h"
using namespace std;

#ifndef LOG_H
#define LOG_H

class Log
{

private:
    ofstream log;

public:
    Log();
    Log(Parameters parameters);
    void writepardouble(string title, double value);
    void writeparstring(string title, string value);
    string filename;
};

#endif // LOG_H
