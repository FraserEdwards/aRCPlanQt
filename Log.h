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
    void collect(Creep creep);
    void collect(Backfill backfill);

};

#endif // LOG_H
