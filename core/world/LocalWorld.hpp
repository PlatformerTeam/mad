#ifndef MAD_CORE_WORLD_LOCALWORLD_HPP
#define MAD_CORE_WORLD_LOCALWORLD_HPP

#include <world/World.hpp>


namespace mad::core {

    class LocalWorld : public World {
    public:
        void manipulate(const Filter &filter, const Intent &intent) override;

    protected:
        void produce_impl(EventDispatcher &dispatcher) override;

    public:

    private:
    };

}


#endif //MAD_CORE_WORLD_LOCALWORLD_HPP
