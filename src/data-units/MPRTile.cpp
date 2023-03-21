

#include <data-units/MPRTile.hpp>
#include <utilities/MPRDispatcher.hpp>


MPRTile::MPRTile(size_t aRow, size_t aCol, size_t aTileRow, size_t aTileCol,
                 const std::vector <double> &aValues,
                 const std::vector <std::string> &aPrecisions) {


    this->mSize = aRow * aCol;

    if (mSize == 0) {
        MPR_API_EXCEPTION(
            "Cannot initialize a Matrix with Dimension equal to 0", -1);
    }

    if (aValues.size() != mSize) {
        MPR_API_EXCEPTION(
            "Values don't cover all the matrix , revisit your data", -1);
    }

    this->mTileSize = aTileRow * aTileCol;
    auto row = aRow / aTileRow;
    auto col = aCol / aTileCol;
    auto required_tiles = mSize / mTileSize;

    if (mSize % mTileSize != 0) {
        MPR_API_EXCEPTION("Tiles should cover the whole Matrix Dimensions", -1);
    }

    if (required_tiles % row != 0 || required_tiles % col != 0) {
        MPR_API_EXCEPTION("Tiles should cover the whole Matrix Dimensions", -1);
    }

    if (required_tiles != aPrecisions.size()) {
        MPR_API_EXCEPTION(
            "Precisions Matrix is incorrect , revisit your Precision Matrix",
            -1);
    }

    this->mpDimensions = new Dimensions(aRow, aCol);
    this->mpTilesDimensions = new Dimensions(row, col);
    this->mpTileInnerDimensions = new Dimensions(aTileRow, aTileCol);
    this->SetMagicNumber();
    this->mTiles.clear();
    this->mTiles.resize(required_tiles);

    for (auto i = 0; i < col; i++) {
        for (auto j = 0; j < row; j++) {
            auto idx = this->GetIndexColumnMajor(std::make_pair(j, i), row);
            auto precision = mpr::precision::GetInputPrecision(
                aPrecisions[ idx ]);
            auto pTile = new DataType(precision);
            pTile->SetSize(this->mTileSize);
            pTile->SetDimensions(aTileRow, aTileCol);
            SIMPLE_DISPATCH(precision, MPRTile::AssignValuesToTile, *pTile, j,
                            i, aValues)
            this->mTiles[ idx ] = pTile;
        }
    }

}

MPRTile::MPRTile(size_t aRow, size_t aCol, size_t aTileRow, size_t aTileCol) {
    this->mSize = aRow * aCol;

    if (mSize == 0) {
        MPR_API_EXCEPTION(
            "Cannot initialize a Matrix with Dimension equal to 0", -1);
    }



    this->mTileSize = aTileRow * aTileCol;
    auto row = aRow / aTileRow;
    auto col = aCol / aTileCol;
    auto required_tiles = mSize / mTileSize;

    if (mSize % mTileSize != 0) {
        MPR_API_EXCEPTION("Tiles should cover the whole Matrix Dimensions", -1);
    }

    if (required_tiles % row != 0 || required_tiles % col != 0) {
        MPR_API_EXCEPTION("Tiles should cover the whole Matrix Dimensions", -1);
    }


    this->mpDimensions = new Dimensions(aRow, aCol);
    this->mpTilesDimensions = new Dimensions(row, col);
    this->mpTileInnerDimensions = new Dimensions(aTileRow, aTileCol);
    this->SetMagicNumber();
    this->mTiles.clear();
    this->mTiles.assign(required_tiles, nullptr);
}


template <typename T>
void
MPRTile::AssignValuesToTile(DataType &aTile, const size_t &aTileRowIdx,
                            const size_t &aTileColIdx,
                            const std::vector <double> &aValues) {
    auto col = aTile.GetNCol();
    auto row = aTile.GetNRow();
    auto pOutput = new T[row * col];
    auto start_idx =
        aTileColIdx * mTileSize * this->mpTilesDimensions->GetNRow();
    start_idx += aTileRowIdx * row;

    size_t offset = 0;

    for (auto i = 0; i < col; i++) {
        std::copy(aValues.begin() + start_idx,
                  aValues.begin() + start_idx + row, pOutput + offset);
        offset += row;
        start_idx += ( this->mpTilesDimensions->GetNRow()) * row;
    }

    aTile.SetData((char *) pOutput);

}


MatrixIndex
MPRTile::GetTileIndex(const MatrixIndex &aMatrixIndex) {
    size_t row_tile =
        aMatrixIndex.first / this->mpTileInnerDimensions->GetNRow();
    size_t col_tile =
        aMatrixIndex.second / this->mpTileInnerDimensions->GetNCol();

    return std::make_pair(row_tile, col_tile);
}


MatrixIndex
MPRTile::GetLocalIndex(const MatrixIndex &aIdxGlobal,
                       const MatrixIndex &aTileIdx) {
    auto row_local = aIdxGlobal.first -
                     ( aTileIdx.first * this->mpTileInnerDimensions->GetNRow());

    auto col_local = aIdxGlobal.second - ( aTileIdx.second *
                                           this->mpTileInnerDimensions->GetNCol());

    return std::make_pair(row_local, col_local);

}


MatrixIndex MPRTile::GetGlobalIndex(const MatrixIndex &aIdxLocal,
                                    const MatrixIndex &aTileIdx) {
    auto row_glob = aIdxLocal.first +
                    ( aTileIdx.first * this->mpTileInnerDimensions->GetNRow());

    auto col_glob = aIdxLocal.second +
                    ( aTileIdx.second * this->mpTileInnerDimensions->GetNCol());
    return std::make_pair(row_glob, col_glob);
}


void
MPRTile::SetVal(const size_t &aRowIdx, const size_t &aColIdx, double aValue) {

    if (CheckIndex(aRowIdx, aColIdx, *this->mpDimensions)) {
        MPR_API_EXCEPTION("Segmentation Fault Index Out Of Bound", -1);
    }

    auto tile_idx = GetTileIndex(std::make_pair(aRowIdx, aColIdx));
    auto local_idx = GetLocalIndex(std::make_pair(aRowIdx, aColIdx), tile_idx);
    auto tile_idx_1d = GetIndexColumnMajor(tile_idx,
                                           this->mpTilesDimensions->GetNRow());

    this->mTiles[ tile_idx_1d ]->SetValMatrix(local_idx.first, local_idx.second,
                                              aValue);

}


double
MPRTile::GetVal(const size_t &aRowIdx, const size_t &aColIdx) {
    if (CheckIndex(aRowIdx, aColIdx, *this->mpDimensions)) {
        MPR_API_EXCEPTION("Segmentation Fault Index Out Of Bound", -1);
    }
    auto tile_idx = GetTileIndex(std::make_pair(aRowIdx, aColIdx));
    auto local_idx = GetLocalIndex(std::make_pair(aRowIdx, aColIdx), tile_idx);
    auto tile_idx_1d = GetIndexColumnMajor(tile_idx,
                                           this->mpTilesDimensions->GetNRow());

    return this->mTiles[ tile_idx_1d ]->GetValMatrix(local_idx.first,
                                                     local_idx.second);
}


void
MPRTile::ChangePrecision(const size_t &aTileRowIdx, const size_t &aTileColIdx,
                         const mpr::precision::Precision &aPrecision) {

    if (CheckIndex(aTileRowIdx, aTileColIdx, *this->mpTilesDimensions)) {
        MPR_API_EXCEPTION("Segmentation Fault Index Out Of Bound", -1);
    }
    auto tile_idx = GetIndexColumnMajor(
        std::make_pair(aTileRowIdx, aTileColIdx),
        this->mpTilesDimensions->GetNRow());

    mTiles[ tile_idx ]->ConvertPrecision(aPrecision);
}


void
MPRTile::PrintTile(const size_t &aTileRowIdx, const size_t &aTileColIdx) {
    if (CheckIndex(aTileRowIdx, aTileColIdx, *this->mpTilesDimensions)) {
        MPR_API_EXCEPTION("Segmentation Fault Index Out Of Bound", -1);
    }
    auto tile_idx = GetIndexColumnMajor(
        std::make_pair(aTileRowIdx, aTileColIdx),
        this->mpTilesDimensions->GetNRow());

    mTiles[ tile_idx ]->Print();
}


bool
MPRTile::CheckIndex(const size_t &aRowIdx, const size_t &aColIdx,
                    const Dimensions &aDimensions) {
    return aRowIdx > aDimensions.GetNRow() ||
           aColIdx > aDimensions.GetNCol() || aRowIdx < 0 ||
           aColIdx < 0;
}


void
MPRTile::ChangePrecision(const size_t &aTileRowIdx, const size_t &aTileColIdx,
                         const std::string &aPrecision) {
    auto precision = GetInputPrecision(aPrecision);
    ChangePrecision(aTileRowIdx, aTileColIdx, precision);
}


void
MPRTile::GetType() {

    std::stringstream ss;
    ss << "----------- MPRTile Object ----------" << std::endl;
    ss << "Number of Rows : " << this->mpDimensions->GetNRow() << std::endl;
    ss << "Number of Cols : " << this->mpDimensions->GetNCol() << std::endl;
    ss << "Number of Tiles : " << this->mSize / this->mTileSize << std::endl;
    ss << "Number of Tiles Per Row : " << this->mpTilesDimensions->GetNRow()
       << std::endl;
    ss << "Number of Tiles Per Col : " << this->mpTilesDimensions->GetNCol()
       << std::endl;
    ss << "Number of Rows Per Tile : "
       << this->mpTileInnerDimensions->GetNRow() << std::endl;
    ss << "Number of Cols Per Tile : "
       << this->mpTileInnerDimensions->GetNCol() << std::endl;
    ss << std::endl;
    ss << "------------------------------------" << std::endl;
#ifdef RUNNING_CPP
    std::cout << std::string(ss.str());
#endif

#ifndef RUNNING_CPP
    Rcpp::Rcout << std::string(ss.str());
#endif

}


void
MPRTile::Print() {
    std::stringstream ss;
    auto stream_size = 100000;
    auto rows_in_tile = this->mpTileInnerDimensions->GetNRow();
    auto cols_tile = this->mpTilesDimensions->GetNCol();
    auto rows_tile = this->mpTilesDimensions->GetNRow();

    this->GetType();

    for (auto i = 0; i < rows_tile; i++) {
        for (auto j = 0; j < rows_in_tile; j++) {
            ss << "[\t";
            for (auto z = 0; z < cols_tile; z++) {
                auto tile_idx = GetIndexColumnMajor(std::make_pair(i, z),
                                                    rows_tile);
                ss << mTiles[ tile_idx ]->PrintRow(j);
            }
            ss << "]" << std::endl;
            if (ss.gcount() > stream_size) {
#ifdef RUNNING_CPP
                std::cout << std::string(ss.str());
#endif

#ifndef RUNNING_CPP
                Rcpp::Rcout << std::string(ss.str());
#endif
                ss.clear();
            }
        }
    }

#ifdef RUNNING_CPP
    std::cout << std::string(ss.str());
#endif

#ifndef RUNNING_CPP
    Rcpp::Rcout << std::string(ss.str());
#endif


}


void
MPRTile::InsertTile(DataType &aTile, const size_t &aTileRowIdx,
                    const size_t &aTileColIdx) {
    auto tileIdx = GetTileIndex(std::make_pair(aTileRowIdx, aTileColIdx));
    auto idx_1D = GetIndexColumnMajor(tileIdx, tileIdx.first);
    if (idx_1D > mTiles.size()) {
        MPR_API_EXCEPTION("Index Out of bound cannot Insert tile", -1);
    }
    if (mTiles[ idx_1D ] != &aTile) {
        delete mTiles[ idx_1D ];
        mTiles[ idx_1D ] = &aTile;
    }
}


SIMPLE_INSTANTIATE(void, MPRTile::AssignValuesToTile, DataType &aTile,
                   const size_t &aTileRowIdx, const size_t &aTileColIdx,
                   const std::vector <double> &aValues)