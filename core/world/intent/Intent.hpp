#ifndef MAD_CORE_WORLD_INTENT_INTENT_HPP
#define MAD_CORE_WORLD_INTENT_INTENT_HPP


namespace mad::core {

    struct Intent {
        enum class Type {
            Lambda
        };

        explicit Intent(Type new_type);

        const Type type;
    };

}


#endif //MAD_CORE_WORLD_INTENT_INTENT_HPP
