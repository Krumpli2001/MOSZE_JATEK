#include <gtest/gtest.h>
#include "gyujteni.hpp"

TEST(Gyujteni_Test, getX)
{
    gyujteni E(1,2,3, false);
    EXPECT_EQ(E.getX(), 1);
}

TEST(Gyujteni_Test, getY)
{
    gyujteni E(1,2,3, false);
    EXPECT_EQ(E.getY(), 2);
}

TEST(Gyujteni_Test, getMennyit_Ad)
{
    gyujteni E(1,2,3, false);
    EXPECT_EQ(E.getMennyit_Ad(), 3);
}

TEST(Gyujteni_Test, getMegvolt_hamis)
{
    gyujteni E(1,2,3, false);
    EXPECT_FALSE(E.getMegvolt());
}

TEST(Gyujteni_Test, getMegvolt_igaz)
{
    gyujteni E(1,2,3, true);
    EXPECT_TRUE(E.getMegvolt());
}

TEST(Gyujteni_Test, setX)
{
    gyujteni E(1,2,3, true);
    E.setX(2);
    EXPECT_EQ(E.getX(), 2);
}

TEST(Gyujteni_Test, setY)
{
    gyujteni E(1,2,3, true);
    E.setX(1);
    EXPECT_EQ(E.getY(), 1);
}

TEST(Gyujteni_Test, setMennyit_Ad)
{
    gyujteni E(1,2,3, false);
    E.setAD(4);
    EXPECT_EQ(E.getMennyit_Ad(), 4);
}

TEST(Gyujteni_Test, setMegvolt)
{
    gyujteni E(1,2,3, false);
    E.setMegvolt(true);
    EXPECT_TRUE(E.getMegvolt());
}