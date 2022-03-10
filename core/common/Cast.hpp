#ifndef MAD_CORE_COMMON_CAST_HPP
#define MAD_CORE_COMMON_CAST_HPP

#include <common/Error.hpp>


namespace mad::core {
    template<typename To, typename From>
    static inline To &cast_to(From &e) {
        To *upcasted_ptr = dynamic_cast<To *>(&e);
        ASSERT(upcasted_ptr != nullptr, "Illegal dynamic cast");
        return *upcasted_ptr;
    }

    template<typename To, typename From>
    static inline const To &const_cast_to(const From &e) {
        const To *upcasted_ptr = dynamic_cast<const To *>(&e);
        ASSERT(upcasted_ptr != nullptr, "Illegal dynamic cast");
        return *upcasted_ptr;
    }

    template<typename To, typename From>
    static inline To &try_cast_to(From &e) {
        To *upcasted_ptr = dynamic_cast<To *>(&e);
        CHECK_THROW(upcasted_ptr != nullptr, IllegalEntityUpcast, "Illegal dynamic cast");
        return *upcasted_ptr;
    }

    template<typename To, typename From>
    static inline const To &try_const_cast_to(const From &e) {
        const To *upcasted_ptr = dynamic_cast<const To *>(&e);
        CHECK_THROW(upcasted_ptr != nullptr, IllegalEntityUpcast, "Illegal dynamic cast");
        return *upcasted_ptr;
    }
}

#endif //MAD_CORE_COMMON_CAST_HPP
