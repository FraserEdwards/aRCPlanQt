#pragma once
#ifndef OutflowProcess_H
#define OutflowProcess_H

class OutflowProcess
{// pressure/time function for outflow from a vessel at defined initial pressure, through a
	private:
		static const short maxTimeSteps;
		double tStarUnchoke;			// Time at which throat unchokes
		double pStarUnchoke;			// Pressure at which throat unchokes
		double tStarOutflow;
		double pp1WhileChoked(double tStar);
		double tStarWhileUnchoked(double xUnch, double pp1);		// Only this inverse function is available
		double X(double pp0);
		double xFunction(double x);

	public:
	    OutflowProcess();											// null constructor
	    OutflowProcess(const double pGauge);						// construct a Control definition from the library or a file
		OutflowProcess& operator=(const OutflowProcess& rhs);
		void pressurePlot();
		double get_tStarOutflow();
};

#endif
