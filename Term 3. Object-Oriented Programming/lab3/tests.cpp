//
// Created by USER on 05.11.2022.
//

//
// Created by USER on 28.09.2022.
//

#include "polynomLib/polynom3V.h"
#include "../../lib/googletest/include/gtest/gtest.h"

TEST(PolyConstructor, DefaultConstructor)
{
    polynoms::Polynom p1;
    ASSERT_STREQ("1.00", p1.getStrPol());
}

TEST(PolyConstructor, InitConstructors)
{
    double arr[] = {27, 27, 9, 1};
    polynoms::Polynom a(1), b(arr), c(arr, 3);
    ASSERT_STREQ("x ^ 1 + 1.00", a.getStrPol());
    ASSERT_STREQ("27.00", b.getStrPol());
    ASSERT_STREQ("x ^ 3 + 9.00 * x ^ 2 + 27.00 * x ^ 1 + 27.00", c.getStrPol());
    ASSERT_ANY_THROW(polynoms::Polynom d(-1));
    ASSERT_ANY_THROW(polynoms::Polynom d(nullptr));

}

TEST(PolyConstructor, CopyConstructor)
{
    double arr[] = {27, 27, 9, 1};
    polynoms::Polynom a(arr, 3), b(a);
    ASSERT_STREQ(a.getStrPol(), b.getStrPol());
}

TEST(PolyFunctions, Funcs)
{
    double arr[] = {27, 27, 9, 1};
    polynoms::Polynom a(arr, 3), b;
    b = a;
    ASSERT_STREQ(a.getStrPol(), b.getStrPol());
    ASSERT_EQ(true, a == b);
    polynoms::Polynom c = a + b;
    ASSERT_STREQ("2.00 * x ^ 3 + 18.00 * x ^ 2 + 54.00 * x ^ 1 + 54.00", c.getStrPol());
    ASSERT_EQ(64, a.PolynomValue(1));
    double dev[] = {27, 18, 3};
    polynoms::Polynom d(dev, 2);
    ASSERT_STREQ(d.getStrPol(), (~a).getStrPol());
    double ost = -3;
    b.divideByXB(ost);
    double div[] = {9, 6, 1};
    polynoms::Polynom e(div, 2);
    ASSERT_STREQ(e.getStrPol(), b.getStrPol());
    ASSERT_EQ(ost, 0);
    double ar2[] = {2, -3 ,1};
    polynoms::Polynom f(ar2, 2);
    ASSERT_ANY_THROW(f.zeroBySegment(0, 3));
    ASSERT_NEAR(1, f.zeroBySegment(0, 1.5), 0.0001);
    ASSERT_NEAR(2, f.zeroBySegment(1.5, 4), 0.0001);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}