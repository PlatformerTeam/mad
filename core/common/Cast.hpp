#ifndef MAD_CORE_COMMON_CAST_HPP
#define MAD_CORE_COMMON_CAST_HPP

#include <common/Error.hpp>

#include <memory>

namespace mad::core {
    template <typename To, typename Pointer, typename From = typename Pointer::element_type>
    static inline auto pointer_cast_to(Pointer ptr_from) {
        auto ptr_to = std::dynamic_pointer_cast<To>(ptr_from);
        ASSERT(ptr_to != nullptr, "Illegal dynamic pointer cast");
        return ptr_to;
    }

    template<typename To, typename From>
    static inline To &cast_to(From &e) {
        To *upcasted_ptr = dynamic_cast<To *>(&e);
        ASSERT(upcasted_ptr != nullptr, "Illegal dynamic cast");
        return *upcasted_ptr;
    }

    template<typename To, typename From>
    static inline const To &const_cast_to(const From &e) {
        const To *upcasted_ptr = dynamic_cast<const To *>(&e);
        ASSERT(upcasted_ptr != nullptr, "Illegal dynamic const cast");
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
        CHECK_THROW(upcasted_ptr != nullptr, IllegalEntityUpcast, "Illegal dynamic const cast");
        return *upcasted_ptr;
    }

    template<typename To, typename From>
    static inline To *cast_to_or_null(From &e) {
        To *upcasted_ptr = dynamic_cast<To *>(&e);
        return upcasted_ptr;
    }
}// namespace mad::core

#endif //MAD_CORE_COMMON_CAST_HPP
