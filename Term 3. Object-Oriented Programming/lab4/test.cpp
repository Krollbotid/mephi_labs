//
// Created by USER on 22.11.2022.
//

/*!
    \file
    \brief tests for AgentLib

    This file has Init-tests for all classes in AgentLib.
*/

#include "AgentLib/table.h"
#include "../../lib/googletest/include/gtest/gtest.h"

TEST(AgenciesConstructor, DefaultConstructor) {
    agencies::Agency a;
    ASSERT_STREQ("Profile", a.getProfile().c_str());
    ASSERT_EQ(0, a.getLicense());
    ASSERT_STREQ("Place", a.getPlace().c_str());
    ASSERT_EQ(agencies::unnamed, a.getType());
    agencies::Printing b;
    ASSERT_EQ(agencies::printing, b.getType());
    ASSERT_EQ(1, b.getPeriod());
    ASSERT_EQ(1, b.getPrintrun());
    agencies::Telecompany c;
    ASSERT_EQ(agencies::telecompany, c.getType());
    ASSERT_EQ(1, c.getFrequency());
    agencies::Radio d;
    std::vector <agencies::FrqDesc> vec = d.getPairs();
    agencies::FrqDesc biba;
    for (int i = 0; i < 3; i++) {
        ASSERT_EQ(biba, vec[i]);
    }
}

TEST(AgenciesConstructor, InitialConstructor) {
    agencies::Agency ag("Profile1", "Place1", 345, agencies::radio);
    ASSERT_EQ(agencies::radio, ag.getType());
    std::string prof = "Profile2", pl = "Place2";
    long long lic = 346;
    agencies::Printing printing1(2, 3), printing2(ag), printing3(prof, pl, lic);
    ASSERT_EQ(2, printing1.getPeriod());
    ASSERT_EQ(3, printing1.getPrintrun());
    ASSERT_EQ(agencies::printing, printing1.getType());
    ASSERT_STREQ("Profile1", printing2.getProfile().c_str());
    ASSERT_EQ(345, printing2.getLicense());
    ASSERT_STREQ("Place1", printing2.getPlace().c_str());
    ASSERT_STREQ("Profile2", printing3.getProfile().c_str());
    ASSERT_EQ(346, printing3.getLicense());
    ASSERT_STREQ("Place2", printing3.getPlace().c_str());
    agencies::Telecompany telecompany1(4), telecompany2(ag), telecompany3(prof, pl, lic);
    ASSERT_EQ(4, telecompany1.getFrequency());
    ASSERT_EQ(agencies::telecompany, telecompany1.getType());
    ASSERT_STREQ("Profile1", telecompany2.getProfile().c_str());
    ASSERT_EQ(345, telecompany2.getLicense());
    ASSERT_STREQ("Place1", telecompany2.getPlace().c_str());
    ASSERT_STREQ("Profile2", telecompany3.getProfile().c_str());
    ASSERT_EQ(346, telecompany3.getLicense());
    ASSERT_STREQ("Place2", telecompany3.getPlace().c_str());
    agencies::FrqDesc frqDesc1(5, 6, 7), frqDesc2(8, 9, 10), frqDescDef;
    std::vector <agencies::FrqDesc> vec = {frqDesc1, frqDesc2, frqDescDef};
    agencies::Radio radio1(vec), radio2(ag), radio3(prof, pl, lic);
    ASSERT_EQ(vec, radio1.getPairs());
    ASSERT_EQ(agencies::radio, radio1.getType());
    ASSERT_STREQ("Profile1", radio2.getProfile().c_str());
    ASSERT_EQ(345, radio2.getLicense());
    ASSERT_STREQ("Place1", radio2.getPlace().c_str());
    ASSERT_STREQ("Profile2", radio3.getProfile().c_str());
    ASSERT_EQ(346, radio3.getLicense());
    ASSERT_STREQ("Place2", radio3.getPlace().c_str());
}

TEST(AgenciesFuncs, Setters) {
    agencies::Printing printing1;
    printing1.setPeriod(2);
    ASSERT_EQ(2, printing1.getPeriod());
    printing1.setPrintrun(3);
    ASSERT_EQ(3, printing1.getPrintrun());
    agencies::Radio radio1;
    agencies::FrqDesc frqDesc1(5, 6, 7), frqDesc2(8, 9, 10), frqDescDef;
    std::vector <agencies::FrqDesc> vec = {frqDesc1, frqDesc2, frqDescDef};
    radio1.setPairs(vec);
    ASSERT_EQ(vec, radio1.getPairs());
}

TEST(AgenciesFuncs, OtherFuncs) {
    agencies::Agency ag("Profile1", "Place1", 345, agencies::radio);
    agencies::Printing printing1(ag, 2, 3), printing2(ag, 2, 3);
    ASSERT_EQ(true, printing1 == printing2);
    ASSERT_STREQ("Profile: Profile1 License: №345 Place: Place1 Type: printing Period: 2 Printrun: 3", printing1.getInfo().c_str());
    agencies::Telecompany telecompany1(ag, 4), telecompany2(ag, 4);
    ASSERT_EQ(true, telecompany1 == telecompany2);
    ASSERT_STREQ("Profile: Profile1 License: №345 Place: Place1 Type: telecompany Frequency: 4.000000", telecompany1.getInfo().c_str());
    agencies::FrqDesc frqDesc1(5, 6, 7), frqDesc2(8, 9, 10), frqDescDef;
    std::vector <agencies::FrqDesc> vec = {frqDesc1, frqDesc2, frqDescDef};
    agencies::Radio radio1(ag, vec), radio2(ag, vec);
    ASSERT_EQ(true, radio1 == radio2);
    ASSERT_STREQ("Profile: Profile1 License: №345 Place: Place1 Type: radio FrqDesc №1 Frequency: 5.000000 "
                 "Range: From: 6.000000 To: 7.000000 FrqDesc №2 Frequency: 8.000000 Range: From: 9.000000 "
                 "To: 10.000000 FrqDesc №3 Frequency: 1.000000 Range: From: 1.000000 To: 2.000000",
                 radio1.getInfo().c_str());
}

TEST(TableAll, TableAll) {
    tables::Table table1;
    ASSERT_STREQ("", table1.printTable().c_str());
    agencies::Agency ag("Profile1", "Place1", 345, agencies::radio);
    auto printing1 = new agencies::Printing(2, 3);
    auto telecompany1 = new agencies::Telecompany(ag, 4);
    agencies::FrqDesc frqDesc1(5, 6, 7), frqDesc2(8, 9, 10), frqDescDef;
    std::vector <agencies::FrqDesc> vec = {frqDesc1, frqDesc2, frqDescDef};
    auto radio1 = new agencies::Radio(vec);
    ASSERT_STREQ("", table1.printTable().c_str());
    table1.insert("PrintingName", printing1);
    table1.insert("TelecompanyName", telecompany1);
    table1.insert("RadioName", radio1);
    std::string s = "Name: PrintingName " + printing1->getInfo() + "\n" + "Name: RadioName " + radio1->getInfo() + "\n"
            + "Name: TelecompanyName " + telecompany1->getInfo() + "\n";
    ASSERT_STREQ(s.c_str(), table1.printTable().c_str());
    tables::Table table2(table1), table3;
    table3 = table1;
    ASSERT_STREQ(s.c_str(), table2.printTable().c_str());
    ASSERT_STREQ(s.c_str(), table3.printTable().c_str());
    std::string g = "Name: TelecompanyName " + telecompany1->getInfo();
    ASSERT_STREQ(g.c_str(), tables::printPair(*(table1.find("TelecompanyName"))).c_str());
    table3.remove("RadioName");
    s = "Name: PrintingName " + printing1->getInfo() + "\n" + "Name: TelecompanyName " + telecompany1->getInfo() + "\n";
    ASSERT_STREQ(s.c_str(), table3.printTable().c_str());
    delete telecompany1;
    delete radio1;
    delete printing1;
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}