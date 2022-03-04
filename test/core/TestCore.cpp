#include <core/Core.hpp>

#include <gtest/gtest.h>

TEST(Core, hello) {
    mad::core::Core object;

    ASSERT_EQ(object.hello(), "Hello from Core\n");
}
