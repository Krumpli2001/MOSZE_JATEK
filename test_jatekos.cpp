#include <gtest/gtest.h>
#include "jatekos.hpp"
#include "Jatekos.cpp"

TEST(Jatekos_Test, getX)
{
    jatekos E(1,2,3);
    EXPECT_EQ(E.getX(), 1);
}

TEST(Jatekos_Test, getY)
{
    jatekos E(1,2,3);
    EXPECT_EQ(E.getY(), 2);
}

TEST(Jatekos_Test, getElet)
{
    jatekos E(1,2,3);
    EXPECT_EQ(E.getElet(), 3);
}

TEST(Jatekos_Test, setElet)
{
    jatekos E(1,2,3);
    E.setElet(5);
    EXPECT_EQ(E.getElet(), 5);
}

TEST(Jatekos_Test, MozgasFel)
{
    jatekos E(1,2,3);
    E.MozgasFel();
    EXPECT_EQ(E.getY(), 1);
}

TEST(Jatekos_Test, MozgasLe)
{
    jatekos E(1,2,3);
    E.MozgasLe();
    EXPECT_EQ(E.getY(), 3);
}

TEST(Jatekos_Test, MozgasBalra)
{
    jatekos E(1,2,3);
    E.MozgasBalra();
    EXPECT_EQ(E.getX(), 0);
}

TEST(Jatekos_Test, MozgasJobbra)
{
    jatekos E(1,2,3);
    E.MozgasJobbra();
    EXPECT_EQ(E.getX(), 1);
}