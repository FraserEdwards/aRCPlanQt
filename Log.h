#include "FracMech.h"

#pragma once
#ifndef LOG_H
#define LOG_H

#include "Backfill.h"
#include "Creep.h"
#include "Log.h"

using namespace std;

class Log : public FracMech, public BeamModel, public Creep, public Backfill
{
private:

public:

    Log();
    Log(Parameters parameters);
    string filename;
    void collect(FracMech fracmech);
    void collect(Creep creep);
    void collect(Backfill backfill);
};

#endif // LOG_H
