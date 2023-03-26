

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
             * @returns
             * MPRTile Matrix containing decomposition result.
             *
             */
            MPRTile *
            TileCholesky(MPRTile &aMatrix);

            /**
             * @brief
             * Tiled-Matrix Multiplication of 2 MPR Tile Matrices
             * performs:
             * x %*% y
             *
             * @param[in] aInputA
             * MPRTile Matrix
             * @param[in] aInputB
             * MPRTile Matrix
             * @returns
             * MPRTile Matrix
             *
             */
            MPRTile *
            TileGemm(MPRTile &aInputA, MPRTile &aInputB);

            /**
             * @brief
             * Accumulates the result of tile A into Tile B
             * Helper Function for TileGemm.
             *
             * @param[in] aInputA
             * MPRTile Matrix
             * @param[in,out] aInputB
             * MPRTile Matrix
             *
             */
            template <typename T>
            void
            AddTiles(DataType &aInputA, DataType &aInputB);

        }
    }
}


#endif //MPR_TILELINEARALGEBRA_HPP
