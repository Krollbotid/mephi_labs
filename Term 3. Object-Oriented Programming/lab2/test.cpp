//
// Created by USER on 28.09.2022.
//

#include "ButaLib/buta.h"
#include <cmath>
#include "../../lib/googletest/include/gtest/gtest.h"

TEST(ButaConstructor, DefaultConstructor)
{
    butas::Buta a1;
    ASSERT_EQ(0, a1.getP().x);
    ASSERT_EQ(0, a1.getP().y);
    ASSERT_EQ(1, a1.getM());
    ASSERT_EQ(2, a1.getC());
}

TEST(ButaConstructor, InitConstructors)
{
    butas::Buta a2(3, 4);
    butas::Point p(2, 3);
    ASSERT_EQ(3, a2.getM());
    ASSERT_EQ(4, a2.getC());
    ASSERT_EQ(0, a2.getP().x);
    ASSERT_EQ(0, a2.getP().y);
    butas::Buta a3(p, 8, 5);
    ASSERT_EQ(2, a3.getP().x);
    ASSERT_EQ(3, a3.getP().y);
    ASSERT_EQ(8, a3.getM());
    ASSERT_EQ(5, a3.getC());
    butas::Buta a4(3, 9, -4, -5);
    ASSERT_EQ(-4, a4.getP().x);
    ASSERT_EQ(-5, a4.getP().y);
    ASSERT_EQ(3, a4.getM());
    ASSERT_EQ(9, a4.getC());
}

TEST(ButaMethods, Setters)
{
    butas::Buta a;
    butas::Point p1(3, 2);
    a.setP(p1);
    ASSERT_EQ(3, a.getP().x);
    ASSERT_EQ(2, a.getP().y);
    butas::Point p2(-3, -2);
    a.setP(p2);
    ASSERT_EQ(-3, a.getP().x);
    ASSERT_EQ(-2, a.getP().y);
    a.setM(2);
    ASSERT_EQ(2, a.getM());
    a.setC(2);
    ASSERT_EQ(2, a.getC());
}

TEST(ButaMethods, Parameters)
{
    butas::Buta a1;
    const double err = 0.00001;
    ASSERT_NEAR(2 * PI, a1.area(), err);
    ASSERT_EQ(4, a1.getFirstCoefficient());
    ASSERT_EQ(0, a1.getSecondCoefficient());
    ASSERT_NEAR(sqrt(2), a1.distance(PI / 4), err);
    ASSERT_STREQ("r ^ 2 = 4.00 * (cos(phi)) ^ 2\n", a1.getPrintableEquation());
    ASSERT_EQ("2 circles", a1.getPrintableType());
    ASSERT_EQ(butas::types::Circles, a1.getType());
    butas::Buta a2(3, 20, 1, 3);
    ASSERT_NEAR(PI * 20, a2.area(), err);
    ASSERT_EQ(38, a2.getFirstCoefficient());
    ASSERT_EQ(-2, a2.getSecondCoefficient());
    ASSERT_NEAR(4.47214, a2.distance(PI / 4), err);
    ASSERT_STREQ("r ^ 2 = 38.00 * (cos(phi)) ^ 2 - (-2.00) * (sin(phi)) ^ 2\n", a2.getPrintableEquation());
    ASSERT_EQ("Elliptic pedal curve", a2.getPrintableType());
    ASSERT_EQ(butas::types::ellipticPedal, a2.getType());
}
int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}