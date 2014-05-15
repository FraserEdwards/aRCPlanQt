#ifndef LOG_H
#define LOG_H

#include "FracMech.h"

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
