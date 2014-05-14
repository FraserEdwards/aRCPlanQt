#ifndef LOG_H
#define LOG_H

#include "Parameters.h"
#include "FracMech.h"
#include "Creep.h"
#include "Backfill.h"
#include "BeamModel.h"
using namespace std;

class Log : public FracMech, private Creep, private Backfill, private BeamModel
{

private:

public:
    Log();
    Log(Parameters parameters);
    string filename;
    void collect(FracMech fracmech);
};

#endif // LOG_H
