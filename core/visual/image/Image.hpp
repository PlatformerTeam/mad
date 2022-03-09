#ifndef MAD_CORE_VISUAL_IMAGE_IMAGE_HPP
#define MAD_CORE_VISUAL_IMAGE_IMAGE_HPP


namespace mad::core {
    class Image {
    public:
        enum class Type {
            Shape,
            StaticImage,
            AnimatedImage,
        };

        const Type type;
    };
}


#endif //MAD_CORE_VISUAL_IMAGE_IMAGE_HPP