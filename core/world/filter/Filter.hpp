#ifndef MAD_CORE_WORLD_FILTER_FILTER_HPP
#define MAD_CORE_WORLD_FILTER_FILTER_HPP


namespace mad::core {

    struct Filter {
        enum class Type {
            Lambda,
            Id,
            Tag,
        };

        const Type type;
    };

}


#endif //MAD_CORE_WORLD_FILTER_FILTER_HPP
