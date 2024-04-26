#include "gtest/gtest.h"
#include "../adder.h"
#include "gmath.h"
#include "gperf.h"
#include <glm/glm.hpp>
TEST(adder, adder) {
    EXPECT_EQ(3, add(1, 2));
}

TEST(t, t1) {
    EXPECT_GT(4, -5);
}

TEST(gmathLib, canUseInGTest) {
    EXPECT_EQ(4, gpower(2));
}

TEST(gperfLib, canUseInGTest) {
    EXPECT_LT(1, GetTicks());
}

TEST(glmLib, canUseInGTest) {
    glm::vec2 v(0.0);
    EXPECT_EQ(0, v.x);
    EXPECT_EQ(0, v.y);
}