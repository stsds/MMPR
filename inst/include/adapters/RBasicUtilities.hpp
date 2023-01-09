
#ifndef MPR_RBASICUTILITIES_HPP
#define MPR_RBASICUTILITIES_HPP

#include <data-units/DataType.hpp>


/**
 * @brief
 * R Adapter for Combining two Matrices by columns
 *
 * @param[in] apInputA
 * MPR Matrix one
 * @param[in] apInputB
 * MPR Matrix two
 *
 * @return
 * MPR Matrix holding combined data
 *
 */
DataType *
RCBind(DataType *apInputA, DataType *apInputB);

/**
 * @brief
 * R Adapter for Combining two Matrices by rows
 *
 * @param[in] apInputA
 * MPR Matrix one
 * @param[in] apInputB
 * MPR Matrix two
 *
 * @return
 * MPR Matrix holding combined data
 *
 */
DataType *
RRBind(DataType *apInputA, DataType *apInputB);

/**
 * @brief
 * R Adapter for Checking if MPR object is 16-bit Precision
 *
 * @param[in] apInput
 * MPR Object
 *
 * @returns
 * True if the object is holding 16-bit precision object,
 * false otherwise
 *
 */
bool
RIsSFloat(DataType *apInput);

/**
 * @brief
 * R Adapter for Checking if MPR object is 32-bit Precision
 *
 * @param[in] apInput
 * MPR Object
 *
 * @returns
 * True if the object is holding 32-bit precision object,
 * false otherwise
 *
 */
bool
RIsFloat(DataType *apInput);

/**
 * @brief
 * R Adapter for Checking if MPR object is 64-bit Precision
 *
 * @param[in] apInput
 * MPR Object
 *
 * @returns
 * True if the object is holding 64-bit precision object,
 * false otherwise
 *
 */
bool
RIsDouble(DataType *apInput);

/**
 * @brief
 * R Adapter for Replicating value(s) number of times
 *
 * @param[in] apInput
 * MPR object to replicate
 * @param[in] aSize
 * Size of output vector
 *
 * @returns
 * MPR Vector Holding Replicated Data
 *
 */
DataType *
RReplicate(DataType *apInput, size_t aSize);

/**
 * @brief
 * R Adapter for Removing NA values from Vector.
 *
 * @param[in,out] apInput
 * MPR Object.
 *
 */
void
RNaExclude(DataType *apInput);

/**
 * @brief
 * R Adapter for Replacing NA values with a given value.
 *
 * @param[in,out] apInput
 * MPR Object.
 * @param[in] aValue
 * Value to use it instead of NA's
 *
 */
void
RNaReplace(DataType *apInput, double aValue);

/**
 * @brief
 * R adapter for Getting Diagonal of a Matrix.
 * MPR Object must be a Matrix
 *
 * @param[in] apInput
 * MPR Matrix
 *
 * @returns
 * MPR Object holding Diagonals
 *
 */
DataType *
RGetDiagonal(DataType *apInput);

/**
 * @brief
 * R adapter for Getting Diagonal of a Matrix.
 * MPR can be a Vector , but dims must be passed
 *
 * @param[in] apInput
 * MPR object can be Vector or Matrix
 * @param[out] aRow
 * Number of Rows
 * @param[in] aCol
 * Number of Cols
 *
 * @returns
 * MPR Object holding Diagonals
 *
 */
DataType *
RGetDiagonalWithDims(DataType *apInput, size_t aRow, size_t aCol);

/**
 * @brief
 * R Adapter for Getting string indicating whether it's 16/32/64 Bit Precision
 *
 * @param[in] apInput
 * MPR object can be Vector or Matrix
 *
 * @returns
 * String Holding Precision Type
 *
 */
std::string
RGetType(DataType *apInput);

/**
 * @brief
 * R Adapter for Getting Min Element in Array
 *
 * @param[in] apInput
 * MPR object can be Vector or Matrix
 *
 * @returns
 * MPR Object holding Minimum Val (Same Precision)
 *
 */
DataType *
RGetMin(DataType *apInput);

/**
 * @brief
 * R Adapter for Getting Min Element Index in Array
 *
 * @param[in] apInput
 * MPR object can be Vector or Matrix
 *
 * @returns
 * Index of Min Element
 *
 */
size_t
RGetMinIdx(DataType *apInput);

/**
 * @brief
 * R Adapter for Getting Max Element in Array
 *
 * @param[in] apInput
 * MPR object can be Vector or Matrix
 *
 * @returns
 * MPR Object holding Maximum Val (Same Precision)
 *
 */
DataType *
RGetMax(DataType *apInput);

/**
 * @brief
 * R Adapter for Getting Max Element Index in Array
 *
 * @param[in] apInput
 * MPR object can be Vector or Matrix
 *
 * @returns
 * Index of Max Element
 *
 */
size_t
RGetMaxIdx(DataType *apInput);

/**
 * @brief
 * R Adapter for Applying operation (+,-,*,/) to the row or column in Matrix.
 *
 * @param[in] apInput
 * MPR Matrix
 * @param[in] apStats
 * the value(s) that should be used in the operation
 * @param[in] aMargin
 * aMargin = 1 means row; aMargin = otherwise means column.
 * @param[in] aOperation
 * char containing operation (+,-,*,/)
 *
 * @returns
 * MPR Vector holding Data After Applying Sweep
 *
 */
DataType *
RSweep(DataType *apInput, DataType *apStats, int aMargin,
       std::string aOperation);

/**
 * @brief
 * R Adapter for Checking Whether Element at index is NAN or Not
 *
 * @param[in] apInput
 * MPR Object
 * @param[in] aIndex
 * Index of Element to check
 *
 * @returns
 * true if NAN,-NAN else Otherwise
 *
 */
bool
RIsNa(DataType *apInput, size_t aIdx);

/**
 * @brief
 * Get total size of Memory used by MPR Object
 *
 * @param[in] apInput
 * MPR Object
 *
 * @returns
 * Total size of Memory used by MPR Object
 *
 */
size_t
RObjectSize(DataType *apInput);

/**
 * @brief
 * R Adapter for Getting Number of Rows
 *
 * @param[in] apInput
 * MPR Object
 *
 * @returns
 * Number of Rows in a Matrix
 */
size_t
RGetNRow(DataType *apInput);

/**
 * @brief
 * R Adapter for Getting Number of Columns
 *
 * @param[in] apInput
 * MPR Object
 *
 * @returns
 * Number of Rows in a Matrix
 */

size_t
RGetNCol(DataType *apInput);

/**
 * @brief
 * R Adapter for Getting Information about MPR object
 * Dimensions-Matrix/Vector-Values ,and Precisions.
 *
 * @param[in] apInput
 * MPR Object.
 *
 * @returns
 * String that will hold the info.
 *
 */
std::string
RPrint(DataType *apInput);

/**
 * @brief
 * R Adapter for Getting Element with Idx from MPR Vector as MPR Object
 *
 * @param[in] apInput
 * MPR Object
 * @param[in] aIndex
 * Index of Data
 *
 * @returns
 * MPR Object holding element at idx
 *
 */
DataType *
RGetElementVector(DataType *apInput, size_t aIndex);

/**
 * @brief
 * R Adapter for Getting Element with Idx [row][col] from MPR Matrix
 * as MPR Object
 *
 * @param[in] apInput
 * MPR Object
 * @param[in] aRow
 * Row Idx
 * @param[in] aCol
 * Col Idx
 *
 * @returns
 * MPR Object holding element at idx
 *
 */
DataType *
RGetElementMatrix(DataType *apInput, size_t aRowIdx,
                  size_t aColIdx);

#endif //MPR_RBASICUTILITIES_HPP