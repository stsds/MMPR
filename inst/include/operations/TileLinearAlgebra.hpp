

#ifndef MPR_TILELINEARALGEBRA_HPP
#define MPR_TILELINEARALGEBRA_HPP

#include <data-units/MPRTile.hpp>


namespace mpr {
    namespace operations {
        namespace linear {

            /**
             * @brief
             * Calculate Cholesky decomposition for Tiled-Symmetric Matrix
             *
             * @param[in] aMatrix
             * MPR Matrix
             * @param[in] aOverWriteInput
             * if true , the input will be overwritten with the output,otherwise
             * a new copy will be created.
             * @returns
             * MPRTile Matrix containing decomposition result.
             *
             */
            MPRTile *
            TileCholesky(MPRTile &aMatrix, const bool &aOverWriteInput = true);

            /**
             * @brief
             * Tiled-Matrix Multiplication of 2 MPR Tile Matrices
             * performs:
             * C = alpha A * B + beta C
             *
             * @param[in] aInputA
             * MPRTile Matrix
             * @param[in] aInputB
             * MPRTile Matrix
             * @param[in,out] aInputC
             * MPRTile Matrix
             * @param[in] aAlpha
             * Factor multiplied to Matrix A
             * @param [in] aBeta
             * Factor multiplied to Matrix C
             * @returns
             * MPRTile Matrix
             *
             */
            MPRTile *
            TileGemm(MPRTile &aInputA, MPRTile &aInputB, MPRTile &aInputC,
                     const double &aAlpha = 1, const double &aBeta = 1);


            /**
             * @brief
             * Solves a triangular matrix equation
             * performs:
             * op(A)*X=alpha*B
             * X*op(A)=alpha*B
             *
             * @param[in] aInputA
             * MPRTile Matrix A
             * @param[in,out] aInputB
             * MPRTile Matrix B, X after returning.
             * @param[in] aSide
             * 'R for Right side , 'L' for Left side
             * @param [in] aUpperTriangle
             * What part of the matrix A is referenced, the opposite triangle
             * being assumed to be zero.
             * if true ,the Upper triangle is referenced. otherwise the Lower.
             * @param[in] aTranspose
             * if true , the transpose of A is used.
             * @param[in] aAlpha
             * Factor used for A , If alpha is zero, A is not accessed.
             *
             *
             */
            void
            TileTrsm(MPRTile &aInputA, MPRTile &aInputB, const char &aSide,
                     const bool &aUpperTriangle, const bool &aTranspose,
                     const double &aAlpha);
        }
    }
}


#endif //MPR_TILELINEARALGEBRA_HPP