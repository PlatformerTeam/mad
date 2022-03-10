#ifndef MAD_CORE_COMMON_CAST_HPP
#define MAD_CORE_COMMON_CAST_HPP

#include <common/Error.hpp>


namespace mad::core {
    class Entity;
}

namespace mad::core {
    template<typename T>
    static inline T &cast_entity(Entity &e) {
        T *upcasted_ptr = dynamic_cast<T *>(&e);
        ASSERT(upcasted_ptr != nullptr, "Illegal dynamic cast");
        return *upcasted_ptr;
    }

    template<typename T>
    static inline const T &const_cast_entity(const Entity &e) {
        const T *upcasted_ptr = dynamic_cast<const T *>(&e);
        ASSERT(upcasted_ptr != nullptr, "Illegal dynamic const cast");
        return *upcasted_ptr;
    }

    template<typename T>
    static inline T &try_cast_entity(Entity &e) {
        T *upcasted_ptr = dynamic_cast<T *>(&e);
        CHECK_THROW(upcasted_ptr != nullptr, IllegalEntityUpcast, "Illegal entity dynamic upcast");
        return *upcasted_ptr;
    }

    template<typename T>
    static inline const T &try_const_cast_entity(const Entity &e) {
        const T *upcasted_ptr = dynamic_cast<const T *>(&e);
        CHECK_THROW(upcasted_ptr != nullptr, IllegalEntityUpcast, "Illegal entity dynamic const upcast");
        return *upcasted_ptr;
    }
}

#endif //MAD_CORE_COMMON_CAST_HPP
