#ifndef MAD_CORE_WORLD_LOCALWORLD_HPP
#define MAD_CORE_WORLD_LOCALWORLD_HPP

#include <world/World.hpp>
#include "event/management/ImmediateDispatcher.h"


namespace mad::core {

    class LocalWorld : public World {
    public:
        bool manipulate(const Filter &filter, const Intent &intent) override;

    protected:
        void produce_impl(EventDispatcher &dispatcher) override;

    public:

    private:
        ImmediateDispatcher dispatcher;
    };

}


#endif //MAD_CORE_WORLD_LOCALWORLD_HPP
