//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//  For the underlying model, see
//  http://www.sciencedirect.com/science/article/pii/S0013794412003530

//  Class containing a finite difference solution to an equivalent beam model
//  An array object representing the opening profile in the open-crack region of a pipe undergoing RCP
//  Uses the symdoublematrix class for a solution

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;

#include "FDprofile.h"

//	Null constructor
FDprofile::FDprofile()
{
    arraySize = 0;
    v_ptr = 0;
    elementsPerUnitLength = 0;
} // end

//	Constructor
FDprofile::FDprofile(const double alpha[2], const double m[2], double zetaBackfilled, double pressurefactor, double residualpressure, short elementsInL, short nodeAtClosure)
{
    elementsPerUnitLength = elementsInL;
    arraySize = nodeAtClosure;                  // Crack-tip and closure points with v* = 0 are not represented

    //  Create and set to zero a matrix [M] of finite difference coefficients
    SymDoubleMatrix mMx(arraySize);
    mMx = 0.0;
    //  …and an RHS vector for pressure forces.
    v_ptr = new double[arraySize];

    double h = 1.0 / float(elementsPerUnitLength);
    //  First disregard backfill attached to the fixed crack-tip node
    zetaBackfilled -= 0.5 * h;

    double mLocal, alphaLocal;
    for (int i = 0; i < arraySize; i++)         // For each row representing a non-boundary point
    {
        //  How much backfill on this element, if any?
        if (zetaBackfilled <= 0.0)
        {   //  No backfill: set alpha[1] and m[1]
            alphaLocal = alpha[1];
            mLocal = m[1];
        }
        else
        {if (zetaBackfilled > h)            //  There's backfill here and beyond
            {   //  Attach an entire backfill element to this point
                alphaLocal = alpha[0];
                mLocal=m[0];
                zetaBackfilled -= h;
            }
            else
            {   //  Hang the leftover part-element of backfill on this element using simple linear interpolation -- FIXME
                alphaLocal = alpha[1] + zetaBackfilled * (alpha[0] - alpha[1]);
                mLocal = m[1] + zetaBackfilled * (m[0] - m[1]);
                zetaBackfilled -= h;    //  Sends it negative: backfill now gone, so no more points need be tested
            }
        }

        //	Set elements on diagonal bands according to the FD equation.
        double h2inv = float(elementsPerUnitLength * elementsPerUnitLength);    // inverse of h^2
        double alpha2 = alphaLocal * alphaLocal;
        double elOnDiagonal = 0.0;
        double el1OffDiagonal = 0.0;
        double el2OffDiagonal = 0.0;

        if (i == 0 or i == (arraySize - 1))         //  First non-boundary FD node
        {
            //  Elements on diagonal:
            elOnDiagonal = 12.0 * h2inv * h2inv     //  4th diff term
                    - alpha2 * h2inv                //  2nd diff term
                    + mLocal;                       //  linear term
            //  Elements one position either side of diagonal:
            el1OffDiagonal = -6.0 * h2inv * h2inv   //  4th diff term
                    + 0.5 * alpha2 * h2inv;         //  2nd diff term
            //  Elements two positions either side of diagonal:
            el2OffDiagonal = 4.0 / 3.0 * h2inv * h2inv;
            //  and all other elements are unchanged.
            if (i == 0)
            {
                mMx.setElement(0, 0, elOnDiagonal);
                mMx.setElement(0, 1, el1OffDiagonal);
                mMx.setElement(0, 2, el2OffDiagonal);
            }
            else
            {
                mMx.setElement(i, i, elOnDiagonal);
                mMx.setElement(i, i-1, el1OffDiagonal);
                mMx.setElement(i, i-2, el2OffDiagonal);

            }
        }
        else    //  Every internal point
        {
            elOnDiagonal = 6.0 * h2inv * h2inv          //  4th diff term
                    - 2.5 * alpha2 * h2inv      //  2nd diff term
                    + mLocal;                   //  linear term
            el1OffDiagonal = -4.0 * h2inv * h2inv       //  4th diff term
                    + 4.0/3.0 * alpha2 * h2inv; //  2nd diff term
            el2OffDiagonal = h2inv * h2inv
                    - alpha2 * h2inv / 12.0;
            mMx.setElement(i, i-2, el2OffDiagonal);     // i=0 case was caught above
            if (i > 1)
                mMx.setElement(i, i-1, el1OffDiagonal); // for i=1 this term not needed
            mMx.setElement(i, i,   elOnDiagonal);
            if (i < (arraySize - 2))
                mMx.setElement(i, i+1, el1OffDiagonal); // for i=(arraySize-2) this term not needed
            mMx.setElement(i, i+2, el2OffDiagonal);     // i=(arraySize-1) case was caught above
        }

        //  Preset RHS to 'residual strain pressure'
        v_ptr[i] = residualpressure;
        //  then add internal pressure in outflow region, decaying linearly over 0 < zeta < 1, and scale total:
        if (i < elementsPerUnitLength)
            v_ptr[i] = pressurefactor * (v_ptr[i] + 1.0 - float(i + 1) / float(elementsPerUnitLength));
    }
    //  *Decompose [M] using LU method, to prepare for solution:
    short error = 0.0;
    mMx.decompose(error);
    //	Solve, putting solution in v_ptr
    mMx.backSubstitute(v_ptr);
    error *= 2.0;
}

// Copy constructor
FDprofile::FDprofile(const FDprofile& original)
{
    arraySize = original.arraySize;
    elementsPerUnitLength = original.elementsPerUnitLength;
    v_ptr = new double[arraySize];
    copy(original);
}

// Copies values of array into *this object, having already checked that size is same
void FDprofile::copy(const FDprofile& original)
{
    double* p = v_ptr + arraySize;
    double* q = original.v_ptr + arraySize;
    while (p > v_ptr)
        *--p = *--q;
}

// Resets size of array, discarding data in it
void FDprofile::resetSize(short newSize)
{
    if (newSize != arraySize) {
        delete [] v_ptr;					// Delete old elements,
        arraySize = newSize;				// set new count,
        v_ptr = new double[newSize];		// and allocate new elements
    }
}

// Assign another FDprofile rhs to this one by operator '='
FDprofile& FDprofile::operator=(const FDprofile& rhs)
{
    if (v_ptr != rhs.v_ptr)
    {
        resetSize(rhs.arraySize);
        copy(rhs);
    }
    elementsPerUnitLength = rhs.elementsPerUnitLength;
    return *this;
}

//	Destructor
FDprofile::~FDprofile()
{
    delete [] v_ptr;
}

// vStar at outflow point
double FDprofile::wStar2()
{
    return v_ptr[elementsPerUnitLength];
}

// Greatest vStar anywhere within open-crack region, found by quadratic interpolation
double FDprofile::wStarMax(short elementsInL)
{
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
}

// 1st derivative of vStar at outflow point
double FDprofile::wStar2dash()
{
    double temp = v_ptr[elementsPerUnitLength-2]
            - 8.0 * v_ptr[elementsPerUnitLength-1]
            + 8.0 * v_ptr[elementsPerUnitLength+1]
            - v_ptr[elementsPerUnitLength+2];
    return temp * float (elementsPerUnitLength) / 12.0;
}

// 2nd derivative of vStar at outflow point
double FDprofile::wStar2dash2()
{
    double temp = -v_ptr[elementsPerUnitLength-2]
            + 16.0 * v_ptr[elementsPerUnitLength-1]
            - 30.0 * v_ptr[elementsPerUnitLength]
            + 16.0 * v_ptr[elementsPerUnitLength+1]
            - v_ptr[elementsPerUnitLength+2];
    return temp * float(elementsPerUnitLength * elementsPerUnitLength) / 12.0;
}

// Simpson trapezoidal integral (vStar dZeta) from crack tip to outflow point
double FDprofile::integral_wStar2()
{
    double simpsonSum = 0.5 * (v_ptr[0] + v_ptr[elementsPerUnitLength]);
    for (int i = 1;  i < elementsPerUnitLength; i++)
        simpsonSum += v_ptr[i];
    return simpsonSum / float(elementsPerUnitLength);
}

// Ratio of 2nd derivatives (closure point / crack tip) using 5-point stencils
double FDprofile::closureMoment()
{
    //	return (v_ptr[arraySize-3] -4.0 * v_ptr[arraySize-2] + 6.0 * v_ptr[arraySize-1])
    //			/ (6.0 * v_ptr[0] - 4.0 * v_ptr[1] + v_ptr[2]);
    return (-v_ptr[arraySize-2] +16.0 * v_ptr[arraySize-1])
            / (16.0 * v_ptr[0] - v_ptr[1]);
}

// Find point within 0 < zeta < 1 at which radial acceleration changes sign, and radial velocity at that point
void FDprofile::findBackfillEjectPoint(double& zetaBackfilled, double& vStarDashBackfillEject)
{
    double interval = 1.0 / float(elementsPerUnitLength);
    short foundIt = false;
    // Second derivative at crack tip, which must be >0:
    double last2ndDeriv = 16.0 * v_ptr[0] - v_ptr[1];
    // Second derivative at node 0
    double this2ndDeriv = -30.0 * v_ptr[0] + 16.0 * v_ptr[1] - v_ptr[2];
    if (this2ndDeriv < 0.0)
    {
        zetaBackfilled = (last2ndDeriv / (last2ndDeriv - this2ndDeriv)) * interval;
        foundIt = true;
    }
    else
    {
        last2ndDeriv = this2ndDeriv;
        this2ndDeriv = 16.0 * v_ptr[0] -30.0 * v_ptr[1] + 16.0 * v_ptr[2] - v_ptr[3];
        if (this2ndDeriv < 0.0)
        {
            zetaBackfilled = (last2ndDeriv / (last2ndDeriv - this2ndDeriv) + 1.0) * interval;
            foundIt = true;
        }
        else
        {
            short i = 2;
            zetaBackfilled = -1.0;
            while (i < elementsPerUnitLength and not foundIt)
            {
                last2ndDeriv = this2ndDeriv;
                this2ndDeriv = -v_ptr[i-2] + 16.0 * v_ptr[i-1] -30.0 * v_ptr[i] + 16.0 * v_ptr[i+1] - v_ptr[i+2];
                if (this2ndDeriv < 0.0)
                {
                    zetaBackfilled = (last2ndDeriv / (last2ndDeriv - this2ndDeriv) + float(i)) * interval;
                    foundIt = true;
                }
                i++;
            }
        }
    }
    //	NB gradient by 5-pt stencil is [(1)(-8)(0)(8)(-1)] / 12h hence interpolation between two adjacent values is
    //  (1 - FractionElementBackfilled) * [(+1)(-8)(+0)(+8)(-1)(+0)]
    //     + FractionElementBackfilled  * [(+0)(+1)(-8)(+0)(+8)(-1)] where 3rd node is 'iMaxBackfilled'.
    double FractionElementBackfilled = zetaBackfilled * float(elementsPerUnitLength);
    short iMaxBackfilled = floor(FractionElementBackfilled);
    FractionElementBackfilled -= float(iMaxBackfilled);
    iMaxBackfilled -= 1;
    vStarDashBackfillEject = -8.0 * FractionElementBackfilled * v_ptr[iMaxBackfilled] + 8.0 * (1.0 - FractionElementBackfilled) * v_ptr[iMaxBackfilled + 1] + (9.0 * FractionElementBackfilled - 1.0) * v_ptr[iMaxBackfilled + 2] - FractionElementBackfilled * v_ptr[iMaxBackfilled + 3];
    if (iMaxBackfilled > 0)
        vStarDashBackfillEject += (9.0 * FractionElementBackfilled - 8.0) * v_ptr[iMaxBackfilled - 1];
    if (iMaxBackfilled > 1)
        vStarDashBackfillEject += (1.0 - FractionElementBackfilled) * v_ptr[iMaxBackfilled - 2];
    vStarDashBackfillEject *= float(elementsPerUnitLength) / 12.0;
} // end backfillEject.

// Returns first node immediately to the left of which the function has a negative minimum
short FDprofile::nodeAtMinimum()
{
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
    {
        // check that neg min is not at last point in array, where next 'thisValue' is boundary zero
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
}

// zeta coordinate of RH boundary point in array = array size
short FDprofile::nodeAtClosure()
{
    return arraySize;
}

// prints displacement output profile
void FDprofile::fprofile()
{
    l=arraySize;
    for (short i=0; i<arraySize; i++)
    {
        zeta.push_back(float(i + 1) / float(elementsPerUnitLength));
        vptra.push_back(float(v_ptr[i]));
    }

}

//Finds outflow values for given parameters
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
}
