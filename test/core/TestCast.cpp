#include <world/entity/Entity.hpp>
#include <common/Cast.hpp>

#include <gtest/gtest.h>

#include <memory>


TEST(Cast, EntityCast) {
    class MockEntity_1 : public mad::core::Entity {
    public:
        MockEntity_1() : Entity(Entity::Type::SimpleObject){};
        void accept(mad::core::World &world,
                    const mad::core::Intent &intent,
                    mad::core::EventDispatcher &dispatcher) override {
        }

    public:
    private:
        int m_field{};
    };

    class MockEntity_2 : public mad::core::Entity {
    public:
        MockEntity_2() : Entity(Entity::Type::SimpleObject){};
        void accept(mad::core::World &world,
                    const mad::core::Intent &intent,
                    mad::core::EventDispatcher &dispatcher) override {
        }

    public:
    private:
        std::string m_field{};
    };

    std::shared_ptr<mad::core::Entity> entity_1 = std::make_shared<MockEntity_1>();
    std::shared_ptr<mad::core::Entity> entity_2 = std::make_shared<MockEntity_2>();

    {
        const mad::core::Entity &const_entity = *entity_1;
        const auto &const_mock_entity = mad::core::const_cast_to<MockEntity_1>(const_entity);
    }

    {
        const mad::core::Entity &const_entity = *entity_1;
        EXPECT_ANY_THROW(mad::core::try_const_cast_to<MockEntity_2>(const_entity));
    }
}
