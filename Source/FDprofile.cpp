#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;

#include "FDprofile.h"

FDprofile::FDprofile()
{//	Null constructor
	arraySize = 0;
	v_ptr = 0;
	elementsPerUnitLength = 0;
} // end


FDprofile::FDprofile(const double alpha[2], const double m[2], double zetaBackfilled, double vStarRes, short elementsInL, short nodeAtClosure)
{//	Constructor
	elementsPerUnitLength = elementsInL;
	arraySize = nodeAtClosure;				// NB. v* = 0 for outermost 'inactive' boundary points, which are not in array

//	Create and set to zero a matrix of finite difference coefficients
	SymDoubleMatrix mMx(arraySize);
	mMx = 0.0;
//	Identify last (highest numbered) node at which backfill is still in contact:
	double bitOfH = zetaBackfilled * float(elementsPerUnitLength);
	short iLeft = floor(bitOfH);
	bitOfH -= float(iLeft);					//  FIXME maybe use this variable later if interpolative weighting is to be used
	iLeft -= 1;
//	Set alpha[1] and m[1], the non-backfilled values, if we are already to right of zetaBackfilled (i.e. there's no backfill here).  Otherwise set backfilled [0] values.
	short noBackfill = iLeft < 0;
	double weight0, weight1, weight2;
	resetBackfill(alpha, m, noBackfill, weight0, weight1, weight2);
//	Set elements on diagonal bands according to the FD equation.	
//	Rows 0 and 1 are hand-made because near boundaries
	mMx.setElement(0, 0, weight0);
	mMx.setElement(0, 1, weight1);
	mMx.setElement(0, 2, weight2);
//
	mMx.setElement(1, 0, weight1);
	mMx.setElement(1, 1, weight0);
	mMx.setElement(1, 2, weight1);
	mMx.setElement(1, 3, weight2);

	for (int i = 2; i < arraySize - 2; i++)	// i.e. for all the rows representing points which are NOT near boundaries
	{ 

		if (i > iLeft and not noBackfill)
		{	// i.e. we have just passed the backfill ejection point
			noBackfill = true;
			resetBackfill(alpha, m, noBackfill,weight0, weight1, weight2);			
		}
		mMx.setElement(i, i-2, weight2);
		mMx.setElement(i, i-1, weight1);
		mMx.setElement(i, i,   weight0);
		mMx.setElement(i, i+1, weight1);
		mMx.setElement(i, i+2, weight2);
	}
//	Likewise, last 2 rows are special
	mMx.setElement(arraySize-1, arraySize-1, weight0);
	mMx.setElement(arraySize-2, arraySize-2, weight0);
	mMx.setElement(arraySize-1, arraySize-2, weight1);
	mMx.setElement(arraySize-2, arraySize-1, weight1);
	mMx.setElement(arraySize-2, arraySize-3, weight1);
	mMx.setElement(arraySize-1, arraySize-3, weight2);
	mMx.setElement(arraySize-2, arraySize-4, weight2);
//	mMx.printMatrix();
// *Decompose [M] using LU method, to prepare for solution:
	short error = 0.0;
	mMx.decompose(error);
	
//	Construct RHS vector for pressure forces and preset it to 'residual strain pressure':
	v_ptr = new double[arraySize];
	noBackfill = iLeft < 0;
	double temp1 = 1.0  / pow(float(elementsPerUnitLength), 4);		// = h^4
	double temp2 = -m[noBackfill] * vStarRes * temp1;

	for (short i = 0;  i < arraySize;  i++)
		v_ptr[i] = temp2; 
	for (int k = 0; k < elementsPerUnitLength;  k++)
	{// internal pressure in outflow region (0 < zeta < 1):
		v_ptr[k] += temp1 * (1.0 - float(k + 1) / float(elementsPerUnitLength));
	}
//	Solve, putting solution in v_ptr
	mMx.backSubstitute(v_ptr);
} // end FDprofile constructor.


FDprofile::FDprofile(const FDprofile& original)
{	// Copy constructor
	arraySize = original.arraySize;
	elementsPerUnitLength = original.elementsPerUnitLength;
	v_ptr = new double[arraySize];
	copy(original);
}//	end copy constructor


void FDprofile::copy(const FDprofile& original)
{	// Copies values of array into *this object, having already checked that size is same
	double* p = v_ptr + arraySize;
	double* q = original.v_ptr + arraySize;
	while (p > v_ptr)
		*--p = *--q;
}//	end copy


void FDprofile::resetSize(short newSize)
{	// Resets size of array, discarding data in it
	if (newSize != arraySize) {
		delete [] v_ptr;					// Delete old elements,
		arraySize = newSize;				// set new count,
		v_ptr = new double[newSize];		// and allocate new elements
	}
}//	end resetSize


FDprofile& FDprofile::operator=(const FDprofile& rhs)
{// Assign another FDprofile rhs to this one by operator '='
	if (v_ptr != rhs.v_ptr)
    {
		resetSize(rhs.arraySize);
		copy(rhs);
    }
	elementsPerUnitLength = rhs.elementsPerUnitLength;
	return *this;
}//	end operator=.


FDprofile::~FDprofile()
{//	Destructor
	delete [] v_ptr;
} // end destructor.


double FDprofile::wStar2()
{// vStar at outflow point
	return v_ptr[elementsPerUnitLength];
} // end wStar2().


double FDprofile::wStarMax(short elementsInL)
{// Greatest vStar anywhere within open-crack region, found by quadratic interpolation
	double y0 = v_ptr[0];
	double y1 = v_ptr[1];
	double y2;
	short i = 2;
	while ((v_ptr[i] > y1) && i < elementsInL)
	{
		y0 = y1;
		y1 = y2;
		y2 = v_ptr[i];
		i++;
	}
	if (i < elementsInL)
	{
		y1 += (y0 - y2) * (y0 - y2) / (y0 - 2.0 * y1 + y2);
	}
	return y1;
} // end wStarMax().


double FDprofile::wStar2dash()
{// 1st derivative of vStar at outflow point
	double temp = v_ptr[elementsPerUnitLength-2]
		- 8.0 * v_ptr[elementsPerUnitLength-1] 

		+ 8.0 * v_ptr[elementsPerUnitLength+1]
		- v_ptr[elementsPerUnitLength+2];
	return temp * float (elementsPerUnitLength) / 12.0;
} // end wStar2dash().


double FDprofile::wStar2dash2()
{// 2nd derivative of vStar at outflow point
	double temp = -v_ptr[elementsPerUnitLength-2]
		+ 16.0 * v_ptr[elementsPerUnitLength-1] 
		- 30.0 * v_ptr[elementsPerUnitLength]
		+ 16.0 * v_ptr[elementsPerUnitLength+1]
		- v_ptr[elementsPerUnitLength+2];
	return temp * float(elementsPerUnitLength * elementsPerUnitLength) / 12.0;
} // end wStar2dash2.


double FDprofile::integral_wStar2()
{// Simpson trapezoidal integral (vStar dZeta) from crack tip to outflow point
	double simpsonSum = 0.5 * (v_ptr[0] + v_ptr[elementsPerUnitLength]);
	for (int i = 1;  i < elementsPerUnitLength; i++)
		simpsonSum += v_ptr[i];
	return simpsonSum / float(elementsPerUnitLength);
} // end integral_wStar2.


double FDprofile::closureMoment()
{// Ratio of 2nd derivatives (closure point / crack tip) using 5-point stencils
//	return (v_ptr[arraySize-3] -4.0 * v_ptr[arraySize-2] + 6.0 * v_ptr[arraySize-1]) 
//			/ (6.0 * v_ptr[0] - 4.0 * v_ptr[1] + v_ptr[2]);
	return (-v_ptr[arraySize-2] +16.0 * v_ptr[arraySize-1]) 
			/ (16.0 * v_ptr[0] - v_ptr[1]);
} // end closureMoment.


void FDprofile::findBackfillEjectPoint(double& zetaBackfillEject, double& vStarDashBackfillEject)
{// Find point within 0 < zeta < 1 at which radial acceleration changes sign, and radial velocity at that point
	double interval = 1.0 / float(elementsPerUnitLength);
	short foundIt = false;
// Second derivative at crack tip, which must be >0:
	double last2ndDeriv = 16.0 * v_ptr[0] - v_ptr[1];
// Second derivative at node 0	
	double this2ndDeriv = -30.0 * v_ptr[0] + 16.0 * v_ptr[1] - v_ptr[2];
	if (this2ndDeriv < 0.0)
	{
		zetaBackfillEject = (last2ndDeriv / (last2ndDeriv - this2ndDeriv)) * interval;
		foundIt = true;
	}
	else
	{
		last2ndDeriv = this2ndDeriv;
		this2ndDeriv = 16.0 * v_ptr[0] -30.0 * v_ptr[1] + 16.0 * v_ptr[2] - v_ptr[3];
		if (this2ndDeriv < 0.0)
		{
			zetaBackfillEject = (last2ndDeriv / (last2ndDeriv - this2ndDeriv) + 1.0) * interval;
			foundIt = true;
		}
		else
		{
			short i = 2;
			zetaBackfillEject = -1.0;
			while (i < elementsPerUnitLength and not foundIt)
			{
				last2ndDeriv = this2ndDeriv;
				this2ndDeriv = -v_ptr[i-2] + 16.0 * v_ptr[i-1] -30.0 * v_ptr[i] + 16.0 * v_ptr[i+1] - v_ptr[i+2];
				if (this2ndDeriv < 0.0)
					{
					zetaBackfillEject = (last2ndDeriv / (last2ndDeriv - this2ndDeriv) + float(i)) * interval;
					foundIt = true;
					}
				i++;	
			}
		}
	}
//	NB gradient by 5-pt stencil is [(1)(-8)(0)(8)(-1)] / 12h hence interpolation between two adjacent values is
//	(1 - bitOfH) * [(+1)(-8)(+0)(+8)(-1)(+0)]
//	   + bitOfH  * [(+0)(+1)(-8)(+0)(+8)(-1)] where 3rd node is 'iLeft'.
	double bitOfH = zetaBackfillEject * float(elementsPerUnitLength);
	short iLeft = floor(bitOfH);
	bitOfH -= float(iLeft);
	iLeft -= 1;
	vStarDashBackfillEject = -8.0 * bitOfH * v_ptr[iLeft] + 8.0 * (1.0 - bitOfH) * v_ptr[iLeft + 1] + (9.0 * bitOfH - 1.0) * v_ptr[iLeft + 2] - bitOfH * v_ptr[iLeft + 3];
	if (iLeft > 0)
		vStarDashBackfillEject += (9.0 * bitOfH - 8.0) * v_ptr[iLeft - 1];
	if (iLeft > 1)
		vStarDashBackfillEject += (1.0 - bitOfH) * v_ptr[iLeft - 2];
	vStarDashBackfillEject *= float(elementsPerUnitLength) / 12.0;
} // end backfillEject.


short FDprofile::nodeAtMinimum()
{// Returns first node immediately to the left of which the function has a negative minimum
	double lastValue = 0.0;					// Boundary value
	double thisValue = v_ptr[0];
	double lastGrad = thisValue;
	double thisGrad = thisValue;
	for (short i = 1; i < arraySize; i++)
	{
		lastValue = thisValue;
		thisValue = v_ptr[i];		
		lastGrad = thisGrad;
		thisGrad = v_ptr[i] - lastValue;
		if (lastValue < 0 and lastGrad * thisGrad < 0)
		{
			if (thisGrad + lastGrad > 0.0)
				return i - 1;
			else
				return i;
		}
	}
	{ // check that neg min is not at last point in array, where next 'thisValue' is boundary zero	
		lastValue = thisValue;
		lastGrad = thisGrad;
		thisGrad = -lastValue;
		if (thisGrad > 0 and lastGrad * lastValue > 0)
		{
			if (lastGrad - lastValue > 0.0)
			{
				return arraySize - 1;
			}
			else
			{
				return arraySize;
			}
		}
	}
	return -1;	// signals that there is NO negative minimum
} // end nodeAtMinimum


short FDprofile::nodeAtClosure()
{// zeta coordinate of RH boundary point in array = array size
	return arraySize;
}// end nodeAtClosure.


void FDprofile::fprofile()
{// prints displacement output profile
	
	l=arraySize;
	for (short i=0; i<arraySize; i++)
    {
		zeta.push_back(float(i + 1) / float(elementsPerUnitLength));
		vptra.push_back(float(v_ptr[i]));
    }
	
}// end printProfile.


void FDprofile::resetBackfill(const double alpha[2],		// 
					const double m[2], 
					int noBackfill,		// = 0 if there is backfill, 1 otherwise
					double& weight0,	// on diagonal
					double& weight1,	// first out from diagonal
					double& weight2)	// second out from diagonal
{// Update alpha and m values to reflect backfill conditions at current node:
	double temp1 = 	1.0 / float(elementsPerUnitLength * elementsPerUnitLength);
	double temp2 = alpha[noBackfill];		// = alpha
	temp2 = temp2 * temp2 * temp1;
	weight1 = 4.0 * (temp2 / 3.0 - 1.0);						
	weight2 = 1.0 - temp2 / 12.0;							
	temp1 *= temp1;							// = h^4
	weight0 = 6 - 2.5 * temp2 + temp1 * m[noBackfill];	// on diagonal
} // end ResetBackfill.

		
void FDprofile::outflowPointValues(double& wStar, double& dwStar_dzeta, double& d2wStar_dZeta2, double& integral_wStar2)
{
	wStar = v_ptr[elementsPerUnitLength];
	double temp = v_ptr[elementsPerUnitLength-2]
		- 8.0 * v_ptr[elementsPerUnitLength-1] 
		+ 8.0 * v_ptr[elementsPerUnitLength+1]
		- v_ptr[elementsPerUnitLength+2];
	dwStar_dzeta = temp * float (elementsPerUnitLength) / 12.0;
	temp = -v_ptr[elementsPerUnitLength-2]
		+ 16.0 * v_ptr[elementsPerUnitLength-1] 
		- 30.0 * v_ptr[elementsPerUnitLength]
		+ 16.0 * v_ptr[elementsPerUnitLength+1]
		- v_ptr[elementsPerUnitLength+2];
	d2wStar_dZeta2 = temp * double(elementsPerUnitLength * elementsPerUnitLength) / 12.0;
	integral_wStar2 = FDprofile::integral_wStar2();
} // end outflowPointValues.
