//     aRCPLan

//     Authors: Dr Patric Leevers, Fraser //
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

#ifndef SymDoubleMatrixH
#define SymDoubleMatrixH


//	A VERY simple class with no exception handling
//  but despite its name it is NOT restricted to symmetrical matrices
class SymDoubleMatrix
{
	public:

        // Create n x n symmetric double matrix
        SymDoubleMatrix(short n);
        // Null constructor:  create 0 x 0 matrix
        SymDoubleMatrix();
        // Delete this matrix
        ~SymDoubleMatrix();
        // Create a copy of the existing matrix a
        SymDoubleMatrix(const SymDoubleMatrix& a);
        // Return value of element (i, j), j>=i
        double getElement(short i, short j);
        // Assign value x to element (i, j), j>=i
        void setElement(short i, short j, double x);
        // Add dx to element (i, j), j>=i
        void incrementElement(short i, short j, double dx);
        // Assignment to scalar by '='
        SymDoubleMatrix& operator=(const double xij);
        // Assignment to matrix by '='
        SymDoubleMatrix& operator=(const SymDoubleMatrix&);
        // Matrix incrementation by operator '+='
        SymDoubleMatrix& operator+=(const SymDoubleMatrix&);
        // Returns number of rows/columns in matrix
        short sizeOf();
        // Change size
        void resetSizeTo(short newSize);
        // Completes matrix by overwriting lower with upper triangle
        void makeSymmetrical();
        // Prints from upper triangular (?  really?) sector
        void printMatrix();
        // Completion and LU decomposition
        void decompose(short& error);
        // Solves [A](x) = (b), then (b) = (x)
        void backSubstitute(double* vVx);
        // Copy in elements of a
        void copy(const SymDoubleMatrix& a);

	private:

        // Number of rows/columns
        short size;
        // Number of elements
        short nElements;
        // Pointer to element array
        double* pointer2elements;
        // Pointer to matrix records row permutations effected by partial pivoting
        short* pointer2indices;
};

#endif
