#include "FracMech.h"
#include "Parameters.h"
#include "Backfill.h"
#include "BeamModel.h"
#include "Creep.h"
using namespace std;

#ifndef LOG_H
#define LOG_H

class Log : public FracMech, public BeamModel, public Creep, public Backfill
{
private:

public:

    Log();
    Log(Parameters parameters);
    string filename;
    void collect(FracMech fracmech);
};

#endif // LOG_H
