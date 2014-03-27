#include "Results.h"

#include <ios>

Results::Results()
{//	Null constructor
//	Open cvs file (for Excel) and shell script (for gnuplot) and print headers/preambles
	results.open("Results.csv",std::fstream::in | std::fstream::out | std::fstream::trunc);
	if(results.fail())
	{
	cout << "Results output file could not be opened.  Is it in use by another application?\n";
	exit(1);
	}
	placeholder("Crack speed");
	placeholder("Decomp. factor");
	placeholder("Speed factor");
	placeholder("Support factor");
	placeholder("Outflow Length");
	placeholder("Flaring (deltaD/D)");
	placeholder("Crack driving force components");
	placeholder("Normalised total");
	newline();	

	results.close();
} // end

void Results::placeholder(string title)
{

	results << title << ",";

}

void Results::cell(double value)
{

	results << value << ",";

}

void Results::newline()
{

	results << "\n";

}

void Results::line(Solution solution)
{
	
		results.open("results.csv",std::fstream::in | std::fstream::out | std::fstream::app);
	    
	    cell(solution.aDotc0[solution.soln]);
	    cell(solution.decompression[solution.soln]);
	    cell(solution.alpha[solution.soln]);
	    cell(solution.m[solution.soln]);
	    cell(solution.outflowLength[solution.soln]);
	    placeholder("   ");
	    cell(solution.gG0[solution.soln]);
	    cell(solution.gTotal[solution.soln]);
	    newline();

		results.close();
}


Results::Results(const Results& original)
{	// Copy constructor
//	arraySize = original.arraySize;
//	elementsPerUnitLength = original.elementsPerUnitLength;
//	v_ptr = new double[arraySize];
//	copy(original);
}//	end copy constructor


void Results::copy(const Results& original)
{	// Copies values of array into *this object, having already checked that size is same
//	double* p = v_ptr + arraySize;
//	double* q = original.v_ptr + arraySize;
//	while (p > v_ptr)
//		*--p = *--q;
}//	end copy


void Results::resetSize(short newSize)
{	// Resets size of array, discarding data in it
//	if (newSize != arraySize) {
//		delete [] v_ptr;					// Delete old elements,
//		arraySize = newSize;				// set new count,
//		v_ptr = new double[newSize];		// and allocate new elements
//	}
}//	end resetSize


//GaDotSolutionFD& GaDotSolutionFD::operator=(const GaDotSolutionFD& rhs)
//{// Assign another GaDotSolutionFD rhs to this one by operator '='
//	if (v_ptr != rhs.v_ptr)
//    {
//		resetSize(rhs.arraySize);
//		copy(rhs);
//    }
//	elementsPerUnitLength = rhs.elementsPerUnitLength;
//	return *this;
//}//	end operator=.


Results::~Results()
{//	Destructor
//	delete [] v_ptr;
	results.close();
} // end destructor.
