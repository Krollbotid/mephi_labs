//
// Created by USER on 22.11.2022.
//

#include "AgentLib/table.h"
#include "../../lib/googletest/include/gtest/gtest.h"

TEST(AgenciesConstructor, DefaultConstructor) {
    Agency a;
    ASSERT_STREQ("Profile", a.getProfile().c_str());
    ASSERT_EQ(0, a.getLicense());
    ASSERT_STREQ("Place", a.getPlace().c_str());
    ASSERT_EQ(unnamed, a.getType());
    Printing b;
    ASSERT_EQ(printing, b.getType());
    ASSERT_EQ(1, b.getPeriod());
    ASSERT_EQ(1, b.getPrintrun());
    Telecompany c;
    ASSERT_EQ(telecompany, c.getType());
    ASSERT_EQ(1, c.getFrequency());
    Radio d;
    std::vector <FrqDesc> vec = d.getPairs();
    FrqDesc biba;
    for (int i = 0; i < 3; i++) {
        ASSERT_EQ(biba, vec[i]);
    }
}

TEST(AgenciesConstructor, InitialConstructor) {
    Agency ag("Profile1", "Place1", 345, radio);
    ASSERT_EQ(radio, ag.getType());
    std::string prof = "Profile2", pl = "Place2";
    long long lic = 346;
    Printing printing1(2, 3), printing2(ag), printing3(prof, pl, lic);
    ASSERT_EQ(2, printing1.getPeriod());
    ASSERT_EQ(3, printing1.getPrintrun());
    ASSERT_EQ(printing, printing1.getType());
    ASSERT_STREQ("Profile1", printing2.getProfile().c_str());
    ASSERT_EQ(345, printing2.getLicense());
    ASSERT_STREQ("Place1", printing2.getPlace().c_str());
    ASSERT_STREQ("Profile2", printing3.getProfile().c_str());
    ASSERT_EQ(346, printing3.getLicense());
    ASSERT_STREQ("Place2", printing3.getPlace().c_str());
    Telecompany telecompany1(4), telecompany2(ag), telecompany3(prof, pl, lic);
    ASSERT_EQ(4, telecompany1.getFrequency());
    ASSERT_EQ(telecompany, telecompany1.getType());
    ASSERT_STREQ("Profile1", telecompany2.getProfile().c_str());
    ASSERT_EQ(345, telecompany2.getLicense());
    ASSERT_STREQ("Place1", telecompany2.getPlace().c_str());
    ASSERT_STREQ("Profile2", telecompany3.getProfile().c_str());
    ASSERT_EQ(346, telecompany3.getLicense());
    ASSERT_STREQ("Place2", telecompany3.getPlace().c_str());
    FrqDesc frqDesc1(5, 6, 7), frqDesc2(8, 9, 10), frqDescDef;
    std::vector <FrqDesc> vec = {frqDesc1, frqDesc2, frqDescDef};
    Radio radio1(vec), radio2(ag), radio3(prof, pl, lic);
    ASSERT_EQ(vec, radio1.getPairs());
    ASSERT_EQ(radio, radio1.getType());
    ASSERT_STREQ("Profile1", radio2.getProfile().c_str());
    ASSERT_EQ(345, radio2.getLicense());
    ASSERT_STREQ("Place1", radio2.getPlace().c_str());
    ASSERT_STREQ("Profile2", radio3.getProfile().c_str());
    ASSERT_EQ(346, radio3.getLicense());
    ASSERT_STREQ("Place2", radio3.getPlace().c_str());
}

TEST(AgenciesFuncs, Setters) {
    Printing printing1;
    printing1.setPeriod(2);
    ASSERT_EQ(2, printing1.getPeriod());
    printing1.setPrintrun(3);
    ASSERT_EQ(3, printing1.getPrintrun());
    Radio radio1;
    FrqDesc frqDesc1(5, 6, 7), frqDesc2(8, 9, 10), frqDescDef;
    std::vector <FrqDesc> vec = {frqDesc1, frqDesc2, frqDescDef};
    radio1.setPairs(vec);
    ASSERT_EQ(vec, radio1.getPairs());
}

TEST(AgenciesFuncs, OtherFuncs) {
    Agency ag("Profile1", "Place1", 345, radio);
    Printing printing1(ag, 2, 3), printing2(ag, 2, 3);
    ASSERT_EQ(true, printing1 == printing2);
    ASSERT_STREQ("Profile: Profile1 License: №345 Place: Place1 Type: printing Period: 2 Printrun: 3", printing1.getInfo().c_str());
    Telecompany telecompany1(ag, 4), telecompany2(ag, 4);
    ASSERT_EQ(true, telecompany1 == telecompany2);
    ASSERT_STREQ("Profile: Profile1 License: №345 Place: Place1 Type: telecompany Frequency: 4.000000", telecompany1.getInfo().c_str());
    FrqDesc frqDesc1(5, 6, 7), frqDesc2(8, 9, 10), frqDescDef;
    std::vector <FrqDesc> vec = {frqDesc1, frqDesc2, frqDescDef};
    Radio radio1(ag, vec), radio2(ag, vec);
    ASSERT_EQ(true, radio1 == radio2);
    ASSERT_STREQ("Profile: Profile1 License: №345 Place: Place1 Type: radio FrqDesc №1 Frequency: 5.000000 "
                 "Range: From: 6.000000 To: 7.000000 FrqDesc №2 Frequency: 8.000000 Range: From: 9.000000 "
                 "To: 10.000000 FrqDesc №3 Frequency: 1.000000 Range: From: 1.000000 To: 2.000000",
                 radio1.getInfo().c_str());
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}