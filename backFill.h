#include "Interface.h"
#include "Parameters.h"
#include "ConfigFile.h"
#include "Filepath.h"

#ifndef _BACKFILL_H
#define _BACKFILL_H

class Backfill
{
	
public:	
	double densityratio;
	Backfill();
	Backfill(const Parameters parameters);

};
#endif
