#ifndef MAD_CORE_VISUAL_IMAGE_IMAGE_HPP
#define MAD_CORE_VISUAL_IMAGE_IMAGE_HPP


namespace mad::core {
    class Image {
    public:
        enum class Type {
            Shape,
            Static,
            Animated
        };

        explicit Image(Type new_type) : type(new_type) {
        }

        virtual ~Image() = default;

        void set_unique_number(int unique_number) {
            m_unique_number = unique_number;
        }

        [[nodiscard]] int get_unique_number() const noexcept {
            return m_unique_number;
        }

        const Type type;

    private:
        int m_unique_number;
    };
}


#endif //MAD_CORE_VISUAL_IMAGE_IMAGE_HPP
