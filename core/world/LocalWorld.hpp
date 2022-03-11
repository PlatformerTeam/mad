#ifndef MAD_CORE_WORLD_LOCALWORLD_HPP
#define MAD_CORE_WORLD_LOCALWORLD_HPP

#include <world/World.hpp>


namespace mad::core {

    class LocalWorld : public World {
    public:
        void manipulate(const Filter &filter, const Intent &intent) override;

        void produce(EventDispatcher &dispatcher) override;
    };

}


#endif //MAD_CORE_WORLD_LOCALWORLD_HPP
