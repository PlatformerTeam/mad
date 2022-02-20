#include <gtest/gtest.h>

#include <Core.h>

using namespace testing;

TEST(Core, a_plus_b_simple) {
core::Core obj;

EXPECT_EQ("Hello from Core\n", obj.hello());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
