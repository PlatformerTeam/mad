#ifndef MAD_CORE_VISUAL_IMAGE_IMAGE_HPP
#define MAD_CORE_VISUAL_IMAGE_IMAGE_HPP

#include <box2d/box2d.h>

#include <memory>

namespace mad::core {

    class Image {
    public:
        enum class Type {
            Shape,
            Static,
            AnimatedOneFile,
            AnimatedSeveralFiles,
            Background,
            Decoration
        };

        enum class Orientation {
            Right, Left
        };

        explicit Image(Type new_type) : type(new_type) {
        }

        virtual ~Image() = default;

        virtual b2PolygonShape as_fixture() = 0;

        const Type type;

        std::shared_ptr<bool> is_active = std::make_shared<bool>(false);

        std::shared_ptr<Orientation> m_orientation = std::make_shared<Orientation>(Orientation::Right);
    };
}


#endif //MAD_CORE_VISUAL_IMAGE_IMAGE_HPP
