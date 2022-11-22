//
// Created by USER on 07.11.2022.
//

#ifndef LAB3_AGENCY_H
#define LAB3_AGENCY_H
#include <iostream>
#include <string>
#include <vector>

namespace agencies {
    enum types {
        unnamed = 0,
        printing = 1, // values written just in case...
        radio = 2,
        telecompany = 3
    };

    std::string getPrintableType(types type);
    types stotypes(const std::string& s);
    std::istream& operator >>(std::istream&, types&);

    class Agency {
    protected:
        std::string profile, place;
        long long license;
        types type;
        virtual std::ostream& printInfo(std::ostream&) const = 0;
        virtual std::istream& learnInfo(std::istream&) = 0;
    public:
        Agency(std::string prof = "Profile", std::string  pl = "Place", long long lic = 0, types typ = unnamed);
        virtual std::string getInfo() const;
        types getType() const;
        std::string getProfile() const;
        std::string getPlace() const;
        long long getLicense() const;
        friend std::ostream& operator <<(std::ostream&, const Agency&);
        friend std::istream& operator >>(std::istream&, Agency&);
    };

    class Printing: public Agency {
    private:
        int period, printrun;
        virtual std::ostream& printInfo(std::ostream&) const = 0;
        virtual std::istream& learnInfo(std::istream&) = 0;
    public:
        Printing(int per = 1, int prtr = 1);
        Printing(Agency &ag, int per = 1, int prtr = 1);
        Printing(std::string prof, std::string pl, long long lic, types typ, int per = 1, int prtr = 1);
        int getPeriod() const;
        int getPrintrun() const;
        std::string getInfo() const;
        Printing& setPeriod(int newPeriod);
        Printing& setPrintrun(int newPrintrun);
    };

    class Telecompany: public Agency {
    private:
        double frequency;
        virtual std::ostream& printInfo(std::ostream&) const = 0;
        virtual std::istream& learnInfo(std::istream&) = 0;
    public:
        Telecompany(double frq = 1);
        Telecompany(Agency &ag, double frq = 1);
        Telecompany(std::string prof, std::string pl, long long lic, types typ, double frq = 1);
        std::string getInfo() const;
    };

    struct FrqDesc {
        double frequency, translationFrom, translationTo;
        FrqDesc(double frq = 1, double from = 1, double to = 2);
        friend std::ostream& operator <<(std::ostream&, const FrqDesc&);
        friend std::istream& operator >>(std::istream&, FrqDesc&);
    };

    class Radio: public Agency {
    private:
        int amount;
        FrqDesc pairs[3];
        virtual std::ostream& printInfo(std::ostream&) const = 0;
        virtual std::istream& learnInfo(std::istream&) = 0;
    public:
        Radio(const std::vector <FrqDesc>& newpairs = {});
        Radio(std::string prof, std::string pl, long long lic, types typ, std::vector <FrqDesc> newpairs = {});
        Radio(Agency &ag, std::vector <FrqDesc> newpairs = {});
        FrqDesc* getPairs() const; // return pointer to dynamic array with size 3. All unused slots are initialized
        // with default values;
        Radio& setPairs(std::vector <FrqDesc> newPairs);
        std::string getInfo() const;
    };
}

#endif //LAB3_AGENCY_H
