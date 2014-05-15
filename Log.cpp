#include <fstream>
#include <iostream>
using namespace std;

#include "Log.h"
#include "File.h"
#include "Parameters.h"
#include "FracMech.h"

Log::Log()
{
    filename = "";
}

Log::Log(Parameters temp)
{

    extern File file;
    filename = "Log/Log.csv";
    file.writeparcsv(temp, filename);
    file.writeheaders(filename);

}

void Log::collect(FracMech fracmech)
{
    extern File file;
    g0 = fracmech.g0;
    file.writelogline(this);

}

void Log::collect(Creep creep)
{
    extern File file;
    diameterRes0 = creep.diameterRes0;
    residualCrackClosure = creep.residualCrackClosure;
    file.writelogline(this);
}

void Log::collect(Backfill backfill)
{
    extern File file;
    densityratio = backfill.densityratio;
    file.writelogline(this);

}


