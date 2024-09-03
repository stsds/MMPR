/**
 * Copyright (c) 2023, King Abdullah University of Science and Technology
 * All rights reserved.
 *
 * MPCR is an R package provided by the STSDS group at KAUST
 *
 **/

#ifndef MPCR_MATHEMATICALOPERATIONS_HPP
#define MPCR_MATHEMATICALOPERATIONS_HPP

#include <data-units/DataType.hpp>


namespace mpcr {
    namespace operations {
        namespace math {


            /**
             * @brief
             * Perform Operation on MPCR Object according to provided Function
             * aFun.
             *
             * @param[in] aInputA
             * MPCR object can be Vector or Matrix
             * @param[out] aOutput
             * MPCR Object can be a vector or a Matrix according to the given inputs
             * @param[in] aFun
             * string indicating which operation to perform
             * currently supported ( abs , ceil , floor , trunc)
             *
             * Note:
             * Function trunc removes all decimals from a given number.
             *
             */
            template <typename T>
            void
            PerformRoundOperation(DataType &aInputA, DataType &aOutput,
                                  std::string aFun);

            /**
             * @brief
             * Perform Square root operation on a given MPCR Object
             *
             * @param[in] aInputA
             * MPCR object can be Vector or Matrix
             * @param[out] aOutput
             * MPCR Object can be a vector or a Matrix according to the given inputs
             *
             */
            template <typename T>
            void
            SquareRoot(DataType &aInputA, DataType &aOutput);

            /**
             * @brief
             * Perform exp operation on a given MPCR Object
             *
             * @param[in] aInputA
             * MPCR object can be Vector or Matrix
             * @param[out] aOutput
             * MPCR Object can be a vector or a Matrix according to the given inputs
             * @param[in] aFlag
             * if true each output value will be subtracted by 1.
             *
             */
            template <typename T>
            void
            Exponential(DataType &aInputA, DataType &aOutput,
                        bool aFlag = false);

            /**
             * @brief
             * Checks if a given MPCR Object values are Finite or not.
             *
             * @param[in] aInputA
             * MPCR object can be Vector or Matrix
             * @param[out] aOutput
             * bool vector . true if finite ,false otherwise
             *
             */

            template <typename T>
            void
            IsFinite(DataType &aInputA, std::vector <int> &aOutput);

            /**
             * @brief
             * Checks if a given MPCR Object values are InFinite or not.
             *
             * @param[in] aInputA
             * MPCR object can be Vector or Matrix
             * @param[out] aOutput
             * int vector . 0 if finite, 1 if infinite ,INT_MIN if NAN
             *
             */
            template <typename T>
            void
            IsInFinite(DataType &aInputA, std::vector <int> &aOutput);

            /**
             * @brief
             * Perform Log operation on a given MPCR Object
             *
             * @param[in] aInputA
             * MPCR object can be Vector or Matrix
             * @param[out] aOutput
             * MPCR Object can be a vector or a Matrix according to the given inputs
             * @param[in] aBase
             * 10 for Log base 10 and 2 for log base 2 ,else it will throw error.
             *
             */
            template <typename T>
            void
            Log(DataType &aInputA, DataType &aOutput, double aBase = 10);

            /**
             * @brief
             * Perform TrigOperation on MPCR Object according to provided
             * Function aFun.
             *
             * @param[in] aInputA
             * MPCR object can be Vector or Matrix
             * @param[out] aOutput
             * MPCR Object can be a vector or a Matrix according to the given inputs
             * @param[in] aFun
             * string indicating which operation to perform
             * currently supported (cos,sin,tan,cosh,sinh,tanh)
             *
             */
            template <typename T>
            void
            PerformTrigOperation(DataType &aInputA, DataType &aOutput,
                                 std::string aFun);

            /**
             * @brief
             * Perform Inverse TrigOperation on MPCR Object according to provided
             * Function aFun.
             *
             * @param[in] aInputA
             * MPCR object can be Vector or Matrix
             * @param[out] aOutput
             * MPCR Object can be a vector or a Matrix according to the given inputs
             * @param[in] aFun
             * string indicating which operation to perform
             * currently supported (acos,asin,atan,acosh,asinh,atanh)
             *
             */
            template <typename T>
            void
            PerformInverseTrigOperation(DataType &aInputA, DataType &aOutput,
                                        std::string aFun);

            /**
             * @brief
             * Rounds a given MPCR Object to a given Number of decimal places.
             *
             * @param[in] aInputA
             * MPCR object can be Vector or Matrix
             * @param[out] aOutput
             * MPCR Object can be a vector or a Matrix according to the given inputs
             * @param[in] aDecimalPoint
             * Number of decimal points to use for rounding.
             *
             */
            template <typename T>
            void
            Round(DataType &aInputA, DataType &aOutput,
                  const int &aDecimalPoint);

            /**
             * @brief
             * Perform Gamma operation on a given MPCR Object
             *
             * @param[in] aInputA
             * MPCR object can be Vector or Matrix
             * @param[out] aOutput
             * MPCR Object can be a vector or a Matrix according to the given inputs
             * @param[in] aLGamma
             * If true lgamma will be used ,otherwise tgamma .
             *
             */
            template <typename T>
            void
            Gamma(DataType &aInputA, DataType &aOutput,
                  const bool &aLGamma = false);


        }
    }
}


#endif //MPCR_MATHEMATICALOPERATIONS_HPP
