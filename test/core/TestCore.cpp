#include <gtest/gtest.h>

TEST(Core, hello) {
    ASSERT_EQ(2 + 2, 4);
}

TEST(Core, other) {
    ASSERT_GE(2 + 2, 4);
}

