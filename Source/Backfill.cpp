//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

//     Class providing a backfill model

#include "cmath"
#include "Backfill.h"

//Null constructor
Backfill::Backfill()
{
    density_ratio=0.0;
}

//Constructor taking paramaters as arguments
//Returns density ratio for backfill
Backfill::Backfill(const Parameters parameters)
{
    //parameters.is_backfilled is divided by 2 to correct the value: should be 1 but is assigned 2 by the checkbox in the GUI
        density_ratio = 1.0 +
            (parameters.backfill_density * parameters.sdr / 2.0 * ((1.0 + 2.0 * parameters.backfill_depth * double(parameters.is_backfilled/2) / parameters.diameter) - 1.0)
            + parameters.water_inside_pipe * pow((parameters.sdr - 1), 2) / (2.0 * parameters.sdr - 1) * 1000.0)  / parameters.density;
			
}
