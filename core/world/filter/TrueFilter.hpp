#ifndef MAD_TRUEFILTER_HPP
#define MAD_TRUEFILTER_HPP

#include "Filter.hpp"

namespace mad::core {

    struct TrueFilter : Filter {

        TrueFilter() : Filter(Filter::Type::True) {
        }

    };

}

#endif //MAD_TRUEFILTER_HPP
