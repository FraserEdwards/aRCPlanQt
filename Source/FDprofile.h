//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

#ifndef FDprofileH
#define FDprofileH

#include <vector>
#include "SymDoubleMatrix.h"

class FDprofile
//  An array object representing the opening profile in the open-crack region of a pipe undergoing RCP
{
	private:
		short arraySize;								// Total number of active nodes
		double* v_ptr;									// Vector of matrix equation RHS elements then, after solution, of vStar elements
	    short elementsPerUnitLength;					// Number of active nodes in outflow length (0 < zeta < 1)
		void resetBackfill(const double alpha[2], const double m[2], int noBackfill, double& weight0, double& weight1, double& weight2);
		void copy(const FDprofile& original);			// Copy

	public:

		int l;
		vector<double> zeta;
		vector <double> vptra;
	    FDprofile();									// Null constructor
	    FDprofile(const double alpha[2], const double m[2], double zetaBackfilled, double vStarRes, short elementsPerUnitLength, short nodeAtClosure);
														// Constructs an FDprofile from the specified BCs
		FDprofile(const FDprofile& original);			// Copy constructor
		FDprofile& operator=(const FDprofile&);			// Assignment by '='
	    ~FDprofile();									// Destructor

		void resetSize(short newSize);					// Resets size or array, discarding data in it

		double wStar2();								// vStar at outflow point
		double wStarMax(short elementsInL);				// Greatest opening
		double wStar2dash();							// 1st derivative of vStar at outflow point
		double wStar2dash2();							// 2nd derivative of vStar at outflow point
		double integral_wStar2();						// Integral (wStar dZeta) of physical opening from crack tip to outflow point
		double closureMoment();							// Ratio of 2nd derivatives (closure point / crack tip)
		void findBackfillEjectPoint(double& zetaBackfillEject, double& vStarDashBackfillEject);
														// 0 < zeta < 1 at which radial acceleration changes sign
		void outflowPointValues(double& wStar, double& dwStar_dzeta, double& d2wStar_dZeta2, double& integral_wStar2);
		short nodeAtMinimum();							// Index of FD point immediately to the right of a negative minimum
		short nodeAtClosure();							// Index of last point in FD array
		void fprofile();
				
};

#endif
