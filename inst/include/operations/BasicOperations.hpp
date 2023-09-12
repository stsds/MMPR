/**
 * Copyright (c) 2023, King Abdullah University of Science and Technology
 * All rights reserved.
 *
 * MPCR is an R package provided by the STSDS group at KAUST
 *
 **/

#ifndef MPCR_BASICOPERATIONS_HPP
#define MPCR_BASICOPERATIONS_HPP

#include <data-units/DataType.hpp>
#include <operations/helpers/BasicOperationsHelper.hpp>


namespace mpcr {
    namespace operations {
        namespace basic {

            /**
             * @brief
             * Get Min/Max Element in Array and Idx at which the element is.
             * if only the Index is Needed ,Empty (size =0) MPCR object should
             * be passed.
             *
             * @param[in] aVec
             * MPCR object can be Vector or Matrix
             * @param[out] aOutput
             * Min/Max Element With the Same input precision as MPCR object
             * @param[out] aMinMaxIdx
             * Index at which Min/Max Element is
             * @param[in] aIsMax
             * bool indicating whether function should return Min or Max
             * True if Max ,False if Min
             *
             */
            template <typename T>
            void
            MinMax(DataType &aVec, DataType &aOutput, size_t &aMinMaxIdx,
                   const bool &aIsMax);

            /**
             * @brief
             * Get string indicating whether it's 16/32/64 Bit Precision
             *
             * @param[in] aVec
             * MPCR object can be Vector or Matrix
             * @param[out] aType
             * String Holding Precision Type
             *
             */
            void
            GetType(DataType &aVec, std::string &aType);

            /**
             * @brief
             * Get Diagonal of a Matrix.
             * if Vector is Being passed to the function its Dimensions Object
             * Must be passed & it should match the Vector size
             *
             * @param[in] aVec
             * MPCR object can be Vector or Matrix
             * @param[out] aOutput
             * MPCR Vector holding Diagonal values
             * @param[in] apDim
             * Dimensions Object in case Vector is used
             *
             */
            template <typename T>
            void
            GetDiagonal(DataType &aVec, DataType &aOutput,
                        Dimensions *apDim = nullptr);

            /**
             * @brief
             * Apply operation (+,-,*,/) to the row or column in Matrix.
             *
             * @param[in] aVec
             * MPCR Matrix
             * @param[in] aStats
             * the value(s) that should be used in the operation
             * @param[out] aOutput
             * MPCR Vector holding Data After Applying Sweep
             * @param[in] aMargin
             * aMargin = 1 means row; aMargin = otherwise means column.
             * @param[in] aFun
             * char containing operation (+,-,*,/,^)
             *
             */
            template <typename T, typename X, typename Y>
            void
            Sweep(DataType &aVec, DataType &aStats, DataType &aOutput,
                  const int &aMargin, const std::string &aFun);

            /**
             * @brief
             * Concatenate one or two vector/Matrix(Row Bind) to a given vector
             *
             * @param[in] aInputA
             * MPCR Vector/Matrix one
             * @param[in] aInputB
             * MPCR Vector/Matrix two
             * @param[in,out] aOutput
             * MPCR Vector/Matrix holding all concatenated data
             * @param[in,out] aCurrentIdx
             * Index to start inserting from ,and it's updated according to next
             * index that should be used for insertion.
             *
             */
            template <typename T, typename X, typename Y>
            void
            Concatenate(DataType &aInputA, DataType &aInputB, DataType &aOutput,
                        size_t &aCurrentIdx);

            /**
             * @brief
             * Combine two Matrices by columns
             *
             * @param[in] aInputA
             * MPCR Matrix one
             * @param[in] aInputB
             * MPCR Matrix two
             * @param[out] aOutput
             * MPCR Matrix holding combined data
             *
             */
            template <typename T, typename X, typename Y>
            void
            ColumnBind(DataType &aInputA, DataType &aInputB, DataType &aOutput);

            /**
             * @brief
             * Combine two Matrices by rows
             *
             * @param[in] aInputA
             * MPCR Matrix one
             * @param[in] aInputB
             * MPCR Matrix two
             * @param[out] aOutput
             * MPCR Matrix holding combined data
             *
             */
            template <typename T, typename X, typename Y>
            void
            RowBind(DataType &aInputA, DataType &aInputB, DataType &aOutput);

            /**
             * @brief
             * Check if MPCR object is 16-bit Precision
             *
             * @param[in] aInput
             * MPCR Object
             * @returns
             * True if the object is holding 16-bit precision object,
             * false otherwise
             *
             */
            bool
            IsSFloat(DataType &aInput);

            /**
             * @brief
             * Check if MPCR object is 32-bit Precision
             *
             * @param[in] aInput
             * MPCR Object
             * @returns
             * True if the object is holding 32-bit precision object,
             * false otherwise
             *
             */
            bool
            IsFloat(DataType &aInput);

            /**
             * @brief
             * Check if MPCR object is 64-bit Precision
             *
             * @param[in] aInput
             * MPCR Object
             * @returns
             * True if the object is holding 64-bit precision object,
             * false otherwise
             *
             */
            bool
            IsDouble(DataType &aInput);

            /**
             * @brief
             * Replicate value(s) number of times
             *
             * @param[in] aInput
             * MPCR object to replicate
             * @param[out] aOutput
             * MPCR Vector holding replicated Data
             * @param[in] aSize
             * Size of output vector
             *
             */
            template <typename T>
            void
            Replicate(DataType &aInput, DataType &aOutput, const size_t &aSize);

            /**
             * @brief
             * Get Information about MPCR object Dimensions-Matrix/Vector-Values
             * Precisions.
             *
             * @param[in] aVec
             * MPCR Object.
             * @param[out] aType
             * String that will hold the info.
             *
             */
            void
            GetAsStr(DataType &aVec, std::string &aType);

            /**
             * @brief
             * Remove NA values from Vector.
             *
             * @param[in,out] aInputA
             * MPCR Object.
             *
             */
            template <typename T>
            void
            NAExclude(DataType &aInputA);

            /**
             * @brief
             * Replace NA values with a given value.
             *
             * @param[in,out] aInputA
             * MPCR Object.
             * @param[in] aValue
             * Value to use it instead of NA's
             *
             */
            template <typename T>
            void
            NAReplace(DataType &aInputA, const double &aValue);

            /**
             * @brief
             * centers the columns of a numeric matrix.
             *
             * @param[in] aInputA
             * MPCR Object.
             * @param[in] aCenter
             * numeric-alike MPCR vector of length equal to the number of
             * columns of aInput.
             * @param[out] aOutput
             * MPCR Output Object
             * @param[in] apCenter
             * bool to indicate whether to center using mean or not.
             * if apCenter is not null, aCenter MPCR object is ignored.
             *
             */
            template <typename T, typename X, typename Y>
            void
            ApplyCenter(DataType &aInputA, DataType &aCenter, DataType &aOutput,
                        const bool *apCenter = nullptr);

            /**
             * @brief
             * Scales the columns of a numeric matrix.
             *
             * @param[in] aInputA
             * MPCR Object.
             * @param[in] aScale
             * numeric-alike MPCR vector of length equal to the number of
             * columns of aInput.
             * @param[out] aOutput
             * MPCR Output Object
             * @param[in] apScale
             * bool to indicate whether to scale using standard deviation or not.
             * if apScale is not null, aScale MPCR object is ignored.
             *
             */
            template <typename T, typename X, typename Y>
            void
            ApplyScale(DataType &aInputA, DataType &aScale,
                       DataType &aOutput, const bool *apScale = nullptr);


        }
    }
}


#endif //MPCR_BASICOPERATIONS_HPP
