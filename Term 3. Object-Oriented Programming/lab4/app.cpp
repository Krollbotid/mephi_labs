#include "AgentLib/table.h"
#include <string>
#include <iostream>

namespace AgentApp {
    const std::string Names[] = {"Unknown", "Printing", "Telecompany", "Radio"};
    const std::string Menu[] = {
            "1. Add an agency",
            "2. Find an agency",
            "3. Delete an agency",
            "4. Replace an agency",
            "5. Show all",
            "6. Show by type",
            "7. BAN agency's license",
            "0. Quit"},
            Choice = "Make your choice",
            Msg = "You are wrong; repeat please";

    const int Num = sizeof(Menu) / sizeof(Menu[0]);

    int Add(tables::Table &), Find(tables::Table &), Remove(tables::Table &), Replace(tables::Table &), ShowAll(
            tables::Table &), ShowByType(tables::Table &), BanLicense(tables::Table &);

    int (*Funcs[])(tables::Table &) = {nullptr, Add, Find, Remove, Replace, ShowAll, ShowByType, BanLicense};


    int Answer(const std::string alt[], int n) {
        int answer;
        std::string prompt = Choice;
        std::cout << "\nWhat do you want to do:" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << alt[i] << std::endl;
        }
        do {
            std::cout << prompt << ": -> ";
            prompt = Msg;
            std::cin >> answer;
            if (!std::cin.good()) {
                std::cout << "Error when number of choice was entered;" << std::endl << "Repeat, please." << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.clear();
            }
        } while (answer < 0 || answer >= n);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return answer;
    }

    const std::string Ag[] = {"1. Printing", "2. Television company", "3. Radio", "0. Quit"};

    const int NumAg = sizeof(Ag) / sizeof(Ag[0]);

    int Add(tables::Table &a) {
        agencies::Agency *ptr = nullptr;
        agencies::Printing p;
        agencies::Telecompany t;
        agencies::Radio r;
        std::string name;
        int ans = Answer(Ag, NumAg);
        while (ans) {
            std::cout << "Enter an Agency name: --> ";
            std::cin >> name;
            if (!std::cin.good())
                throw std::logic_error("Error when an agency name was entered");
            switch (ans) {
                case 1:
                    std::cout << "Enter profile(string), license(integer value no bigger than 2^63 - 1), place(string),"
                                 " period(integer value no bigger than 2^31 - 1), "
                                 "printrun(integer value no bigger than 2^31 - 1):" << std::endl;
                    ptr = &p;
                    break;
                case 2:
                    std::cout << "Enter profile(string), license(integer value no bigger than 2^63 - 1), place(string),"
                                 " frequency(floating):" << std::endl;
                    ptr = &t;
                    break;
                case 3:
                    std::cout << "Enter profile(string), license(integer value no bigger than 2^63 - 1), place(string),"
                                 " amount of frequency sets(integer value from [1,3]), and each set in following order:"
                                 "\nfrequency, borders of translating range(all three values are floating)";
                    ptr = &r;
                    break;
            }
            try {
                std::cin >> (*ptr);
            } catch (std::exception &ex) {
                std::cout << ex.what() << std::endl;
                delete ptr;
                ptr = nullptr;
            }
            if (!std::cin.good())
                throw std::logic_error("Error when Agency values were entered");
            std::cin.ignore(80, '\n');
            if (a.insert(name, *ptr))
                std::cout << "Ok" << std::endl;
            else
                std::cout << "Duplicate name" << std::endl;
            ans = Answer(Ag, NumAg);
        }
        return 0;
    }

    int Find(tables::Table &a) {
        std::string name;
        tables::Table::Const_Iterator it;
        const agencies::Agency *ptr;
        std::cout << "Enter an agency name: --> ";
        std::cin >> name;
        if (!std::cin.good())
            throw std::logic_error("Error when an agency name was entered");
        it = a.find(name);
        if (it == a.end()) {
            std::cout << "The Agency with Name \"" << name << "\" is absent in container"
                      << std::endl;
            return -1;
        }
        ptr = (*it).second;
        std::cout << "The Agency with Name \"" << (*it).first
                  << "\" is a " << Names[ptr->getType()]
                  << std::endl;
        std::cout << (*ptr) << std::endl;
        return 0;
    }

    int Remove(tables::Table &a) {
        std::string name;
        std::cout << "Enter an agency name: --> ";
        std::cin >> name;
        if (!std::cin.good())
            throw std::logic_error("Error when an agency name was entered");
        if (a.remove(name))
            std::cout << "Ok" << std::endl;
        else
            std::cout << "The Agency with Name \"" << name << "\" is absent in container"
                      << std::endl;
        return 0;
    }

    int Replace(tables::Table &a) {
        agencies::Agency *ptr = nullptr;
        agencies::Printing p;
        agencies::Telecompany t;
        agencies::Radio r;
        std::string name;
        std::cout << "Enter an agency name for replace: --> ";
        std::cin >> name;
        if (!std::cin.good())
            throw std::logic_error("Error when an agency name was entered");
        int ans;
        ans = Answer(Ag, NumAg);
        switch (ans) {
            case 1:
                std::cout << "Enter profile(string), license(integer value no bigger than 2^63 - 1), place(string),"
                             " period(integer value no bigger than 2^31 - 1), "
                             "printrun(integer value no bigger than 2^31 - 1):" << std::endl;
                ptr = &p;
                break;
            case 2:
                std::cout << "Enter profile(string), license(integer value no bigger than 2^63 - 1), place(string),"
                             " frequency(floating):" << std::endl;
                ptr = &t;
                break;
            case 3:
                std::cout << "Enter profile(string), license(integer value no bigger than 2^63 - 1), place(string),"
                             " amount of frequency sets(integer value from [1,3]), and each set in following order:"
                             "\nfrequency, borders of translating range(all three values are floating)";
                ptr = &r;
                break;
        }
        try {
            std::cin >> (*ptr);
        } catch (std::exception &ex) {
            std::cout << ex.what() << std::endl;
            delete ptr;
            ptr = nullptr;
        }
        if (!std::cin.good())
            throw std::logic_error("Error when Agency values were entered");
        std::cin.ignore(80, '\n');
        if (a.replace(name, *ptr))
            std::cout << "Ok" << std::endl;
        else
            std::cout << "The Agency with Name \"" << name << "\" is absent in container"
                      << std::endl;
        return 0;
    }

    int ShowAll(tables::Table &a) {
        std::cout << a << std::endl;
        return 0;
    }

    int ShowByType(tables::Table &a) {
        int ans = Answer(Ag, NumAg);
        tables::Table::Const_Iterator it;
        for(it = a.begin(); it != a.end(); ++it) {
            if ((*it).second->getType() == ans) {
                std::cout << (*it).second->getInfo() << std::endl;
            }
        }
        return 0;
    }

    int BanLicense(tables::Table &a) {
        std::string name;
        tables::Table::Const_Iterator it;
        agencies::Agency *ptr;
        std::cout << "Enter an agency name: --> ";
        std::cin >> name;
        if (!std::cin.good())
            throw std::logic_error("Error when an agency name was entered");
        it = a.find(name);
        if (it == a.end()) {
            std::cout << "The Agency with Name \"" << name << "\" is absent in container"
                      << std::endl;
            return -1;
        }
        ptr = (*it).second;
        ptr->banLicense();
        return 0;
    }
}

int main()
{
    tables::Table ar;
    try {
        int ind = AgentApp::Answer(AgentApp::Menu, AgentApp::Num);
        while (ind) {
            AgentApp::Funcs[ind](ar);
            ind = AgentApp::Answer(AgentApp::Menu, AgentApp::Num);
        }
        std::cout << "That's all. Bye!" << std::endl;
    }
    catch (const std::exception &er)
    {
        std::cout << er.what() << std::endl;
    }
    return 0;
}