/**
 * Copyright (c) 2023, King Abdullah University of Science and Technology
 * All rights reserved.
 *
 * MPCR is an R package provided by the STSDS group at KAUST
 *
 **/

#ifndef MPCR_DATATYPE_HPP
#define MPCR_DATATYPE_HPP


#include <vector>
#include <data-units/Precision.hpp>


/** Dimensions struct holding Dimensions for Representing a Vector as a Matrix **/
typedef struct Dimensions {

    /** size_t representing number of Rows in a Matrix**/
    size_t mCol;
    /** size_t representing number of Columns in a Matrix**/
    size_t mRow;

    /**
     * @brief
     * Default Constructor
     */
    Dimensions() = default;


    /**
     * @brief
     * Dimensions Constructor
     *
     * @param[in] aRow
     * Number of Rows in a Matrix
     * @param[in] aCol
     * Number of Columns in a Matrix
     *
     */
    explicit
    Dimensions(size_t aRow, size_t aCol) {
        this->mRow = aRow;
        this->mCol = aCol;
    }


    /**
     * @brief
     * Dimensions Constructor
     *
     * @param[in] aDimensions
     * Dimensions struct object to copy its dimensions
     */
    Dimensions(const Dimensions &aDimensions) {
        this->mRow = aDimensions.mRow;
        this->mCol = aDimensions.mCol;
    }


    /**
     * @brief
     * Dimensions Copy Constructor
     *
     * @param[in] aDimensions
     * Dimensions struct object to copy its dimensions
     */
    Dimensions &
    operator =(const Dimensions &aDimensions) = default;


    /**
     * @brief
     * Get Number of Rows
     *
     * @returns
     * Number of Rows in a Matrix
     */
    inline
    size_t
    GetNRow() const {
        return this->mRow;
    }


    /**
     * @brief
     * Get Number of Columns
     *
     * @returns
     * Number of Columns in a Matrix
     */
    inline
    size_t
    GetNCol() const {
        return this->mCol;
    }


    /**
     * @brief
     * Set Number of Columns
     *
     * @param[in] aCol
     * Number of Columns in a Matrix
     */
    void
    SetNCol(size_t aCol) {
        this->mCol = aCol;
    }


    /**
     * @brief
     * Set Number of Rows
     *
     * @param[in] aRow
     * Number of Rows in a Matrix
     */
    void
    SetNRow(size_t aRow) {
        this->mRow = aRow;
    }


    /**
     * @brief
     * Default De-Constructor
     */
    ~Dimensions() = default;

} Dimensions;


/** DataType Class creates an array of (16/32/64)-Bit Precision that you can access throw
 * R as C++ object. Can Be represented as Matrix with Column Major representation.
 **/
class DataType {

public:

    /**
     * @brief
     * DataType default constructor
     */
    DataType() = default;

    /**
     * @brief
     * DataType Constructor
     *
     * @param[in] aSize
     * Size of Vector
     * @param[in] aPrecision
     * Precision to Describe the Values (as a Precision ENUM object)
     */
    DataType(size_t aSize, mpcr::precision::Precision aPrecision);

    /**
     * @brief
     * DataType Constructor from a vector
     *
     * @param[in] aValues
     * Vector of values
     * @param[in] aPrecision
     * Precision to Describe the Values (as a Precision ENUM object)
     */
    DataType(std::vector <double> &aValues,
             mpcr::precision::Precision aPrecision);


    /**
     * @brief
     * DataType Constructor from a vector
     *
     * @param[in] aValues
     * Vector of values
     * @param[in] aPrecision
     * Precision to Describe the Values (as a string Precision)
     */
    DataType(std::vector <double> aValues, std::string aPrecision);


    /**
     * @brief
     * DataType Matrix Constructor from a vector of values.
     *
     * @param[in] aValues
     * Vector of values
     * @param[in] aRow
     * Number of Rows.
     * @param[in] aCol
     * Number of Cols.
     * @param[in] aPrecision
     * Precision to Describe the Values (as a Precision ENUM object)
     */
    DataType(std::vector <double> &aValues, const size_t &aRow,
             const size_t &aCol, const std::string &aPrecision);

    /**
     * @brief
     * DataType Copy Constructor
     *
     * @param[in] aDataType
     * DataType object to copy its content
     */
    DataType(const DataType &aDataType);

    /**
     * @brief
     * DataType Copy Constructor with a given Precision
     *
     * @param[in] aDataType
     * DataType object to copy its content
     */
    DataType(DataType &aDataType, const mpcr::precision::Precision &aPrecision);

    /**
     * @brief
     * DataType Constructor
     *
     * @param[in] aSize
     * Size of Vector
     * @param[in] aPrecision
     * Precision to Describe the Values (as a String)
     */
    DataType(size_t aSize, const std::string &aPrecision);

    /**
     * @brief
     * DataType Constructor
     *
     * @param[in] aRow
     * Number Of Rows in Matrix
     * @param[in] aCol
     * Number Of Columns in Matrix
     * @param[in] aPrecision
     * Precision to Describe the Values (as a Precision ENUM object)
     */
    DataType(size_t aRow, size_t aCol, mpcr::precision::Precision aPrecision);

    /**
     * @brief
     * DataType Constructor
     *
     * @param[in] aSize
     * Size of Vector
     * @param[in] aPrecision
     * Precision to Describe the Values (as an int)
     */
    DataType(size_t aSize, int aPrecision);

    /**
     * @brief
     * DataType Constructor ,Creates Datatype Object with nothing more than a
     * precision initialized
     *
     * @param[in] aPrecision
     * Precision to Describe the Values (as a Precision ENUM object)
     */
    explicit
    DataType(mpcr::precision::Precision aPrecision);

    /**
     * @brief
     * DataType Copy Operator
     *
     * @param[in] aDataType
     * DataType object to copy its content
     */
    DataType &
    operator =(const DataType &aDataType);

    /**
     * @brief
     * R-Adapter for Performing Plus Operation on MPCR Object
     *
     * @param[in] aObj
     * MPCR Object or Numerical Value
     * @returns
     * MPCR Object
     *
     */
    DataType *
    PerformPlusDispatcher(SEXP aObj);

    /**
     * @brief
     * R-Adapter for Performing Minus Operation on MPCR Object
     *
     * @param[in] aObj
     * MPCR Object or Numerical Value
     * @returns
     * MPCR Object
     *
     */
    DataType *
    PerformMinusDispatcher(SEXP aObj);

    /**
     * @brief
     * R-Adapter for Performing Multiply Operation on MPCR Object
     *
     * @param[in] aObj
     * MPCR Object or Numerical Value
     * @returns
     * MPCR Object
     *
     */
    DataType *
    PerformMultDispatcher(SEXP aObj);

    /**
     * @brief
     * R-Adapter for Performing Division Operation on MPCR Object
     *
     * @param[in] aObj
     * MPCR Object or Numerical Value
     * @returns
     * MPCR Object
     *
     */
    DataType *
    PerformDivDispatcher(SEXP aObj);

    /**
     * @brief
     * R-Adapter for Performing Power Operation on MPCR Object
     *
     * @param[in] aObj
     * MPCR Object or Numerical Value
     * @returns
     * MPCR Object
     *
     */
    DataType *
    PerformPowDispatcher(SEXP aObj);

    /**
     * @brief
     * R-Adapter for Checking Whether MPCR Object is Greater than aObj
     *
     * @param[in] aObj
     * MPCR Object or Numerical Value
     * @returns
     * R-Vector/Matrix of Bool Values
     *
     */
    SEXP
    GreaterThanDispatcher(SEXP aObj);

    /**
     * @brief
     * R-Adapter for Checking Whether MPCR Object is Greater than or equal aObj
     *
     * @param[in] aObj
     * MPCR Object or Numerical Value
     * @returns
     * R-Vector/Matrix of Bool Values
     *
     */
    SEXP
    GreaterThanOrEqualDispatcher(SEXP aObj);

    /**
     * @brief
     * R-Adapter for Checking Whether MPCR Object is Less than aObj
     *
     * @param[in] aObj
     * MPCR Object or Numerical Value
     * @returns
     * R-Vector/Matrix of Bool Values
     *
     */
    SEXP
    LessThanDispatcher(SEXP aObj);

    /**
     * @brief
     * R-Adapter for Checking Whether MPCR Object is Less than or equal aObj
     *
     * @param[in] aObj
     * MPCR Object or Numerical Value
     * @returns
     * R-Vector/Matrix of Bool Values
     *
     */
    SEXP
    LessThanOrEqualDispatcher(SEXP aObj);

    /**
     * @brief
     * R-Adapter for Checking Whether MPCR Object is Equal to aObj
     *
     * @param[in] aObj
     * MPCR Object or Numerical Value
     * @returns
     * R-Vector/Matrix of Bool Values
     *
     */
    SEXP
    EqualDispatcher(SEXP aObj);

    /**
     * @brief
     * R-Adapter for Checking Whether MPCR Object is Not Equal to aObj
     *
     * @param[in] aObj
     * MPCR Object or Numerical Value
     * @returns
     * R-Vector/Matrix of Bool Values
     *
     */
    SEXP
    NotEqualDispatcher(SEXP aObj);

    /**
     * @brief
     * DataType De-Constructor
     */
    ~DataType();


    /**
     * @brief
     * DataType ClearUp Function to Clear all Pointers and data inside except
     * Precision
     */
    inline void
    ClearUp() {
        this->mSize = 0;
        this->mMatrix = false;
        delete[] this->mpData;
        delete this->mpDimensions;
        this->mpData = nullptr;
        this->mpDimensions = nullptr;
    }


    /**
     * @brief
     * Changes a Vector to a Matrix
     *
     * @param[in] aRow
     * Number Of Rows in Matrix
     * @param[in] aCol
     * Number Of Columns in Matrix
     */
    void
    ToMatrix(size_t aRow, size_t aCol);

    /**
     * @brief
     * Changes a Matrix to a Vector
     */
    void
    ToVector();

    /**
     * @brief
     * Prints all data in the Vector
     */
    void
    Print();

    /**
     * @brief
     * Get Values in the Vector according to Index (0-based Indexing)
     *
     * @param[in] aIndex
     * Index in vector
     *
     * @returns
     * Value with idx=aIndex in vector
     */
    double
    GetVal(size_t aIndex);

    /**
     * @brief
     * Get Values in the Matrix according to Index (0-based Indexing)
     *
     * @param[in] aRow
     * Row Index
     * @param[in] aCol
     * Col Index
     *
     * @returns
     * Value at idx [row][col]
     */
    double
    GetValMatrix(const size_t &aRow, const size_t &aCol);

    /**
     * @brief
     * Set Values in the Vector according to Index (0-based Indexing)
     *
     * @param[in] aIndex
     * Index in Vector
     * @param[in] aVal
     * Value used to set the vector[idx] with
     */
    void
    SetVal(size_t aIndex, double aVal);

    /**
     * @brief
     * Set Values in the Matrix according to Row,col (0-based Indexing)
     *
     * @param[in] aRow
     * Row Index
     * @param[in] aCol
     * Column Index
     * @param[in] aVal
     * Value used to set the vector[idx] with
     */
    void
    SetValMatrix(size_t aRow, size_t aCol, double aVal);

    /**
     * @brief
     * Get Precision of the Object
     *
     * @returns
     * Precision Object
     */
    mpcr::precision::Precision &
    GetPrecision();

    /**
     * @brief
     * Get Data of Vector
     *
     * @returns
     * Char pointer pointing to vector data (Must be casted according to precision)
     */
    char *
    GetData();

    /**
     * @brief
     * Get Size of Vector or Matrix
     *
     * @returns
     * Size of Vector or total size of Matrix
     */
    size_t
    GetSize() const;

    /**
     * @brief
     * Set Size of Vector or Matrix
     *
     * @param[in] aSize
     * Size of Matrix or Vector
     */
    void
    SetSize(size_t aSize);

    /**
     * @brief
     * Set Precision of Vector or Matrix (Currently it clears up all data)
     *
     * @param[in] aPrecision
     * Precision of Vector or Matrix
     */
    void
    SetPrecision(mpcr::precision::Precision aPrecision);

    /**
     * @brief
     * bool indicating whether it's a Matrix or Vector
     *
     * @returns
     * True if it's a Matrix ,False otherwise
     */
    bool
    IsMatrix() const;

    /**
     * @brief
     * Get Index of Matrix in Row-Wise Representation
     *
     * @param[in] aRow
     * Index Of Row in Matrix
     * @param[in] aCol
     * Index Of Column in Matrix
     *
     * @returns
     * Index in 1D representation
     */
    size_t
    GetMatrixIndex(size_t aRow, size_t aCol);

    /**
     * @brief
     * Set Data Buffer. (Clears the Current Buffer)
     *
     * @param[in] aData
     * Buffer to set Object Buffer With.
     */
    void
    SetData(char *aData);

    /**
     * @brief
     * Get Number of Rows
     *
     * @returns
     * Number of Rows in a Matrix
     */
    size_t
    GetNRow() const;

    /**
     * @brief
     * Get Number of Columns
     *
     * @returns
     * Number of Columns in a Matrix
     *
     */
    size_t
    GetNCol() const;

    /**
     * @brief
     * Set Matrix Dimensions (throw Error in case the Dimensions can't cover all
     * the data available)
     *
     * @param[in] aRow
     * Number Of Rows in Matrix
     * @param[in] aCol
     * Number Of Columns in Matrix
     */
    void
    SetDimensions(size_t aRow, size_t aCol);

    /**
     * @brief
     * Get Matrix Dimensions
     *
     * @returns
     * Dimensions struct containing the Dimensions of the Matrix
     */
    Dimensions *
    GetDimensions() const;


    /**
     * @brief
     * Return whether this Dimensions can be used to convert Vector to Matrix
     *
     * @returns
     * true if the given Row and Col covers all the data in the buffer,
     * false otherwise
     *
     */
    inline
    bool
    CanBeMatrix(size_t aRow, size_t aCol) const {
        return (( aRow * aCol ) == this->mSize );
    }


    /**
     * @brief
     * Check Whether Element at index is NAN or Not
     *
     * @param[in] aIndex
     * Index of Element to check
     *
     * @returns
     * true if NAN,-NAN else Otherwise
     *
     */
    bool
    IsNA(const size_t &aIndex);

    /**
     * @brief
     * Check Whether MPCR Elements are NA or Not
     *
     * @param[in] apDimensions
     * Dimensions to set incase MPCR Object is a Matrix.
     *
     * @returns
     * true if NAN,-NAN else Otherwise
     *
     */
    std::vector <int> *
    IsNA(Dimensions *&apDimensions);

    /**
     * @brief
     * Get total size of Memory used by MPCR Object
     *
     * @returns
     * Total size of Memory used by MPCR Object
     *
     */
    size_t
    GetObjectSize();


    /**
     * @brief
     * Get Element at Idx from MPCR Vector as MPCR Object
     *
     * @param[in] aIndex
     * Index to Get Value from
     *
     * @returns
     * MPCR Object holding element at idx
     *
     */
    inline
    DataType *
    GetElementVector(const size_t &aIndex) {
        auto element = GetVal(aIndex);
        auto output = new DataType(1, this->mPrecision);
        output->SetVal(0, element);
        return output;
    }


    /**
     * @brief
     * Get Element with Idx [row][col] from MPCR Matrix as MPCR Object
     *
     * @param[in] aRow
     * Row Idx
     * @param[in] aCol
     * Col Idx
     *
     * @returns
     * MPCR Object holding element at idx
     *
     */
    inline
    DataType *
    GetElementMatrix(const size_t &aRow, const size_t &aCol) {
        auto index = GetMatrixIndex(aRow, aCol);
        auto element = GetVal(index);
        auto output = new DataType(1, this->mPrecision);
        output->SetVal(0, element);
        return output;
    }


    /**
     * @brief
     * Check if a Casted Memory Address is a DataType.
     *
     * @returns
     * true if the casted pointer is a DataType Object, False Otherwise
     */
    inline
    const bool
    IsDataType() const {
        return ( this->mMagicNumber == 911 );
    }


    /**
     * @brief
     * Convert MPCR Object Precision
     *
     * @param[in] aPrecision
     * Required MPCR Precision
     *
     */
    void
    ConvertPrecision(const mpcr::precision::Precision &aPrecision);

    /**
     * @brief
     * Convert MPCR Values to R-Numeric Vector (vector double will be wrapped to
     * match R-Numeric Vector)
     *
     * @returns
     * Vector of Double Values
     */
    std::vector <double>
    ConvertToNumericVector();

    /**
     * @brief
     * Convert MPCR Values to R-Numeric Matrix
     *
     * @returns
     * R- Numeric Matrix
     *
     */
    Rcpp::NumericMatrix
    ConvertToRMatrix();


    /**
     * @brief
     * Set MPCR Object Dimensions according to given input
     *
     * @param[in] aInput
     * MPCR Object
     *
     */
    inline
    void
    SetDimensions(DataType &aInput) {
        this->mSize = aInput.mSize;
        if (aInput.mMatrix) {
            this->SetDimensions(aInput.GetNRow(), aInput.GetNCol());
        }
    }


    /**
     * @brief
     * Transpose MPCR Matrix
     *
     */
    void
    Transpose();

    /**
     * @brief
     * Set and cast values in the data vector according to Vector of double values
     *
     * @param[in] aValues
     * vector of double values
     *
     */
    void
    SetValues(std::vector <double> &aValues);

    /**
     * @brief
     * Print a whole Row (given) in case of Matrix .
     * used for printing MPCR Tile
     *
     * @param[in] aRowIdx
     * Row Idx to Print
     *
     * @returns
     * string holding values in the given row without brackets, only spacing is
     * applied.
     *
     */
    std::string
    PrintRow(const size_t &aRowIdx);

    /**
     * @brief
     * Fills Upper or Lower Triangle with a given value
     * Note:
     * the Input must be a square Matrix
     *
     * @param[in] aValue
     * value to use for filling the triangle
     * @param[in] aUpperTriangle
     * bool to indicate whether to fill the upper or the lower triangle
     * if true, the upper triangle will be accessed ;otherwise, the lower
     *
     */
    void
    FillTriangle(const double &aValue, const bool &aUpperTriangle = true);

    /**
     * @brief
     * Returns the sum of all elements in MPCR Object
     *
     * @returns
     * Sum of all elements
     *
     */
    double
    Sum();

    /**
     * @brief
     * Returns the square sum of all elements in MPCR Object
     *
     * @returns
     * Square sum of all elements
     *
     */
    double
    SquareSum();

    /**
     * @brief
     * Returns the product of all elements in MPCR Object
     *
     * @returns
     * Product of all elements
     *
     */
    double
    Product();

    /**
     * @brief
     * Returns the determinant of all elements in MPCR Object
     *
     * @returns
     * Determinant of all elements
     *
     */
    double
    Determinant();

    /**
     * @brief
     * Serialize DataType object as a vector of char
     *
     * @returns
     * vector of bytes containing DataType object as a stream of bytes
     *
     */
    std::vector <char>
    Serialize();

    /**
     * @brief
     * R version to Serialize DataType object as a Raw Vector
     *
     * @returns
     * vector of bytes containing DataType object as a stream of bytes
     *
     */
    Rcpp::RawVector
    RSerialize();

    /**
     * @brief
     * R version to DeSerialize Stream of bytes to MPCR Object
     *
     * @param[in] aInput
     * vector of bytes containing DataType object as a stream of bytes
     *
     */
    static DataType *
    RDeSerialize(Rcpp::RawVector aInput);

    /**
     * @brief
     * DeSerialize Stream of bytes to MPCR Object
     *
     * @param[in] aInput
     * vector of bytes containing DataType object as a stream of bytes
     *
     */
    static DataType *
    DeSerialize(char *apData);


private:

    /**
     * @brief
     * Get Values in the Vector according to Index (0-based Indexing) and
     * Precision type
     *
     * @param[in] aIndex
     * Index in Vector
     * @param[out] aOutput
     * Value at idx
     *
     */
    template <typename T>
    void
    GetValue(size_t aIndex, double &aOutput);

    /**
     * @brief
     * Set Values in the Vector according to Index (0-based Indexing) and
     * Precision type
     *
     * @param[in] aIndex
     * Index in Vector
     * @param[in] aVal
     * Value to set index with
     */
    template <typename T>
    void
    SetValue(size_t aIndex, double &aVal);

    /**
     * @brief
     * Prints all data in the Vector according to its type
     */
    template <typename T>
    void
    PrintVal();

    /**
     * @brief
     * Copies Data From Src buffer to Dest Buffer
     *
     * @params[in] aSrc
     * Buffer to copy from
     * @params[out] aDest
     * Buffer to copy to
     *
     */
    template <typename T>
    void
    GetCopyOfData(const char *apSrc, char *&apDest);

    /**
     * @brief
     * Copies Data From Src buffer to Dest Buffer
     *
     * @params[in] aSrc
     * Buffer to copy from
     * @params[out] aDest
     * Buffer to copy to
     *
     */
    template <typename T, typename X, typename Y>
    void
    GetCopyOfData(DataType &aSrc, DataType &aDestination);


    /**
     * @brief
     * Initialize Data Buffer according to its type
     */
    template <typename T>
    void
    Init(std::vector <double> *aValues = nullptr);

    /**
     * @brief
     * Check Whether Element at Index is NAN or Not
     *
     * @param[in] aIndex
     * Index of Element to check
     * @param[out] aFlag
     * True if NAN,-NAN else otherwise
     *
     */
    template <typename T>
    void
    CheckNA(const size_t &aIndex, bool &aFlag);

    /**
     * @brief
     * Check Whether Elements in MPCR Objects are NA
     *
     * @param[in] aOutput
     * Logical Output Int Vector 1/TRUE 0/FALSE
     * @param[out] apDimensions
     * Dimensions to set incase MPCR Object is Matrix
     *
     */
    template <typename T>
    void
    CheckNA(std::vector <int> &aOutput, Dimensions *&apDimensions);

    /**
     * @brief
     * Get total size of Memory used by Data in MPCR Object
     *
     * @param[out] aDataSize
     * Total size of Memory used by Data in MPCR Object
     *
     */
    template <typename T>
    void
    GetDataSize(size_t &aDataSize);

    /**
     * @brief
     * Set Magic Number To Check For DataType Object.
     *
     */
    void
    SetMagicNumber();

    /**
     * @brief
     * Convert MPCR Object Precision
     *
     * @param[in] aPrecision
     * Required MPCR Precision
     *
     */
    template <typename T>
    void
    ConvertPrecisionDispatcher(const mpcr::precision::Precision &aPrecision);

    /**
     * @brief
     * Convert MPCR Values to R-Numeric Vector (vector double will be wrapped to
     * match R-Numeric Vector)
     *
     * @param[in] aOutput
     * Vector of Double Values
     *
     */
    template <typename T>
    void
    ConvertToVector(std::vector <double> &aOutput);

    /**
     * @brief
     * Convert MPCR Values to R-Numeric Matrix
     *
     * @param[in] aOutput
     * R- Numeric Matrix
     *
     */
    template <typename T>
    void
    ConvertToRMatrixDispatcher(Rcpp::NumericMatrix *&aOutput);

    /**
     * @brief
     * Dispatcher for transposing data matrix according to precision
     *
     */
    template <typename T>
    void
    TransposeDispatcher();


    /**
     * @brief
     * Dispatcher for printing one Row of the Matrix
     *
     * @param[in] aRowIdx
     * Row Idx to Print
     * @param[in,out] aRowAsString
     * string stream to print data into.
     *
     */
    template <typename T>
    void
    PrintRowsDispatcher(const size_t &aRowIdx, std::stringstream &aRowAsString);

    /**
     * @brief
     * Dispatcher for calculating the sum of all elements in MPCR Object
     *
     * @param[out] aResult
     * Sum of all elements
     *
     */
    template <typename T>
    void
    SumDispatcher(double &aResult);

    /**
     * @brief
     * Dispatcher for calculating the square sum of all elements in MPCR Object
     *
     * @param[out] aResult
     * square sum of all elements
     *
     */
    template <typename T>
    void
    SquareSumDispatcher(double &aResult);

    /**
     * @brief
     * Dispatcher for calculating the product of all elements in MPCR Object
     *
     * @param[out] aResult
     * Product of all elements
     *
     */
    template <typename T>
    void
    ProductDispatcher(double &aResult);

    /**
     * @brief
     * Dispatcher for calculating the determinant of all elements in MPCR Object
     *
     * @param[out] aResult
     * determinant of all elements
     *
     */
    template <typename T>
    void
    DeterminantDispatcher(double &aResult);

    /**
     * @brief
     * Dispatcher for Filling the Upper or Lower Triangle with a given value
     * Note:
     * the Input must be a square Matrix
     *
     * @param[in] aValue
     * value to use for filling the triangle
     * @param[in] aUpperTriangle
     * bool to indicate whether to fill the upper or the lower triangle
     * if true, the upper triangle will be accessed ;otherwise, the lower
     *
     */
    template <typename T>
    void
    FillTriangleDispatcher(const double &aValue,
                           const bool &aUpperTriangle = true);


    /** Buffer Holding the Data **/
    char *mpData;
    /** Dimensions object that describe the Vector as a Matrix **/
    Dimensions *mpDimensions;
    /** Total size of Vector or Matrix (Data Buffer) **/
    size_t mSize;
    /** Precision used to describe the data buffer **/
    mpcr::precision::Precision mPrecision;
    /** Bool indicating whether it's a Matrix(True) or Vector(False) **/
    bool mMatrix;
    /** Magic Number to check if object is DataType **/
    int mMagicNumber;


};


#endif //MPCR_DATATYPE_HPP
