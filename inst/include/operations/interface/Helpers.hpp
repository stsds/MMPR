

#ifndef MPCR_HELPERS_HPP
#define MPCR_HELPERS_HPP


#include <utilities/MPCRDispatcher.hpp>
#include <data-units/DataType.hpp>

namespace mpcr {
    namespace operations {
        namespace helpers {
            template <typename T>
            class Helpers {

            public:
                Helpers() = default;

                ~Helpers() = default;


                virtual
                void
                Symmetrize(DataType &aInput, const bool &aToUpperTriangle,
                           kernels::RunContext *aContext)=0;


                virtual
                void
                Reverse(DataType &aInput, kernels::RunContext *aContext)=0;


                virtual
                void
                Transpose(DataType &aInput, kernels::RunContext *aContext)=0;


                virtual
                void
                FillTriangle(DataType &aInput, const double &aValue,
                             const bool &aUpperTriangle,
                             kernels::RunContext *aContext)=0;

            };
            MPCR_INSTANTIATE_CLASS(Helpers)
        }
    }
}
#endif //MPCR_HELPERS_HPP
