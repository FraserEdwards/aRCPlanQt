#include <fstream>
#include <iostream>
using namespace std;

#include "Log.h"
#include "File.h"
#include "Parameters.h"

Log::Log()
{
    filename = "";
}

Log::Log(Parameters temp)
{

    extern File file;
    filename = "/Log/Log.csv";
    file.writeparcsv(temp, filename);
    file.writeheaders(filename);

}


