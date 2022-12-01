#include <gtest/gtest.h>
#include "ellenseg.hpp"

TEST(Ellenseg_Test, getX)
{
    ellenseg E(1,2,3);
    EXPECT_EQ(E.getX(), 1);
}

TEST(Ellenseg_Test, getY)
{
    ellenseg E(1,2,3);
    EXPECT_EQ(E.getY(), 2);
}

TEST(Ellenseg_Test, getSebzes)
{
    ellenseg E(1,2,3);
    EXPECT_EQ(E.getSebzes(), 3);
}