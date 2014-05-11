#include <fstream>
#include <iostream>

#include "Log.h"
#include "File.h"
#include "Parameters.h"

Log::Log()
{
    filename = "";

}

Log::Log(Parameters parameters)
{

    extern File file;

    filename = "Log.csv";

    log.open((file.directory + "Log/" + filename).c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);

    log << "Input Parameters\n" << " \n";

    writeparstring("Material ID", parameters.matID);
    writepardouble("Density", parameters.density);
    writepardouble("Dynamic Modulus", parameters.eDyn0degC);
    writepardouble("Delta Dynamic Modulus", parameters.dEdyndT);
    writepardouble("Creep Modulus", parameters.creepModulus);
    writepardouble("Poisson", parameters.poisson);

    writeparstring("Pipe ID", parameters.pipeID);
    writepardouble("Diameter", parameters.diameter);
    writepardouble("SDR", parameters.sdr);
    writepardouble("Notch depth", parameters.notchDepth);
    writepardouble("Diameter Creep Ratio", parameters.diameterCreepRatio);

    writeparstring("Test method ID", parameters.methodID);
    writepardouble("Fullscale", parameters.fullScale);
    writepardouble("Temperature", parameters.tempDegC);
    writepardouble("Initial pressure", parameters.p0bar);
    writepardouble("Backfilled", parameters.isBackfilled);
    writepardouble("Backfill depth", parameters.backfillDepth);
    writepardouble("Backfill density", parameters.backfillDensity);
    writepardouble("Fraction of Internal Volume as Solid", parameters.solidInsidePipe);
    writepardouble("Fraction of Internal Volume as Water", parameters.waterInsidePipe);

    writepardouble("Outflow Model", parameters.outflowModelOn);
    writepardouble("Outflow length", parameters.lambda);
    writepardouble("Single mode", parameters.singlemode);
    writepardouble("Non-dimensional crack speed", parameters.aDotc0);
    writepardouble("Elements", parameters.elementsinl);


    switch(parameters.varname)
    {
        case 0:
            writeparstring("Independent variable", "Non-dimensional speed");
            break;
        case 1:
            writeparstring("Independent variable", "Pressure");
            break;
        case 2:
             writeparstring("Independent variable", "Temperature");
            break;
    }

    log.close();
}

void Log::writepardouble(string title, double value)
{

    log << title << "," << value << "\n";

}

void Log::writeparstring(string title, string value)
{

      log << title << "," << value << "\n";

}
