#include <iostream>
using namespace std;

#include "Plot.h"
#include "gnuplotHandle.hpp"

Plot::Plot()
{

}

void Plot::handler(Solution solution)
{

	results(solution.aDotc0, solution.decompression, "Decompression factor with respect to dimensionless crack speed", "Results/", "Dimensionless crack speed", "Decompression factor");
	results(solution.aDotc0, solution.alpha, "Speed factor with respect to dimensionless crack speed", "Results/", "Dimensionless crack speed", "Speed factor, {/Symbol a}");
	results(solution.aDotc0, solution.m, "Support factor with respect to aDotc0", "Results/", "Dimensionless crack speed", "Dimensionless pipe flaring modulus");
	results(solution.aDotc0, solution.outflowLength, "Dimensionless outflow length with respect to dimensionless crack speed", "Results/", "Dimensionless crack speed", "Dimensionless outflow length, {/Symbol l}");
	results(solution.aDotc0, solution.deltaDStar, "Flaring with respect to dimensionless crack speed", "Results/", "Dimensionless crack speed", "Flaring");
	results(solution.aDotc0, solution.gG0, "Crack driving force with respect to dimensionless crack speed", "Results/", "Dimensionless crack speed", "Crack driving force");
	results(solution.aDotc0, solution.gTotal, "Dimensionless crack driving force with respect to dimensionless crack speed", "Results/", "Dimensionless crack speed", "Dimensionless crack driving force");

}

void Plot::profile(vector<double> x, vector<double> y, string title, string folder, double titlevalue, string xaxis, string yaxis)
{

	//plots displacement output profile
	extern string location;
	char buffer[5];
	snprintf(buffer, sizeof(buffer), "%g", titlevalue);
	
	filename= location + string("/Plots/") + folder + title + buffer;
	
	Gnuplot g1;
	g1.cmd("set terminal postscript enhanced");
	g1.set_xlabel(xaxis).set_ylabel(yaxis);
	g1.savetops(filename);
	g1.plot_xy(x,y,"points");	
		
}

void Plot::results(vector<double> x, vector<double> y, string title, string folder, string xaxis, string yaxis)
{

	//plots displacement output profile
	extern string location;
	
	filename= location + string("/Plots/") + folder + title;
	
	Gnuplot g1;
	g1.cmd("set terminal postscript enhanced");
	g1.set_xlabel(xaxis).set_ylabel(yaxis);
	g1.savetops(filename);
	g1.plot_xy(x,y,"points");	

}

