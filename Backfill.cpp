#include "cmath"
#include "Backfill.h"

Backfill::Backfill()
{
	densityratio=0.0;
}

Backfill::Backfill(const Parameters parameters)
{

		densityratio = 1.0 +
			(parameters.backfillDensity * parameters.sdr / 2.0 * ((1.0 + 2.0 * parameters.backfillDepth * double(parameters.isBackfilled) / parameters.diameter) - 1.0)
			+ parameters.waterInsidePipe * pow((parameters.sdr - 1), 2) / (2.0 * parameters.sdr - 1) * 1000.0)  / parameters.density;
			
}
