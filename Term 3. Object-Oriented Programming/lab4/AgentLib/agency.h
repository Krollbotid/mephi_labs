//
// Created by USER on 07.11.2022.
//

#ifndef LAB4_AGENCY_H
#define LAB4_AGENCY_H
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
        virtual std::ostream& printInfo(std::ostream&) const;
        virtual std::istream& learnInfo(std::istream&);
        virtual bool isEqual(const Agency*) const;
    public:
        Agency(std::string prof = "Profile", std::string pl = "Place", const long long &lic = 0,
               const types &typ = unnamed);
        virtual ~Agency() {};
        virtual Agency *clone() const;
        virtual std::string getInfo() const;
        types getType() const;
        std::string getProfile() const;
        std::string getPlace() const;
        long long getLicense() const;
        friend std::ostream& operator <<(std::ostream&, const Agency&);
        friend std::istream& operator >>(std::istream&, Agency&);
        friend bool operator ==(const Agency&, const Agency&);

    };

    class Printing: public Agency {
    private:
        int period, printrun;
        virtual std::ostream& printInfo(std::ostream&) const;
        virtual std::istream& learnInfo(std::istream&);
        virtual bool isEqual(const Agency*) const;
    public:
        Printing(const int &per = 1, const int &prtr = 1);
        Printing(const Agency &ag, const int &per = 1, const int &prtr = 1);
        Printing(const std::string& prof, const std::string& pl, const long long &lic, const int &per = 1, const int &prtr = 1);
        virtual Agency *clone() const;
        int getPeriod() const;
        int getPrintrun() const;
        std::string getInfo() const;
        Printing& setPeriod(int newPeriod);
        Printing& setPrintrun(int newPrintrun);

    };

    class Telecompany: public Agency {
    private:
        double frequency;
        virtual std::ostream& printInfo(std::ostream&) const;
        virtual std::istream& learnInfo(std::istream&);
        virtual bool isEqual(const Agency*) const;
    public:
        Telecompany(const double &frq = 1);
        Telecompany(const Agency &ag, const double &frq = 1);
        Telecompany(const std::string &prof, const std::string &pl, const long long &lic, const double &frq = 1);
        virtual Agency *clone() const;
        double getFrequency() const;
        std::string getInfo() const;
    };

    struct FrqDesc {
        double frequency, translationFrom, translationTo;
        FrqDesc(const double &frq = 1, const double &from = 1, const double &to = 2);
        friend std::ostream& operator <<(std::ostream&, const FrqDesc&);
        friend std::istream& operator >>(std::istream&, FrqDesc&);
        friend bool operator ==(const FrqDesc&, const FrqDesc&);
        friend bool operator !=(const FrqDesc&, const FrqDesc&);
    };

    class Radio: public Agency {
    private:
        int amount;
        FrqDesc pairs[3];
        virtual std::ostream& printInfo(std::ostream&) const;
        virtual std::istream& learnInfo(std::istream&);
        virtual bool isEqual(const Agency*) const;
    public:
        Radio(const std::vector <FrqDesc>& newpairs = {});
        Radio(const std::string &prof, const std::string &pl, const long long &lic, const std::vector <FrqDesc> &newpairs = {});
        Radio(const Agency &ag, const std::vector <FrqDesc> &newpairs = {});
        virtual Agency *clone() const;
        std::vector <FrqDesc> getPairs() const; // return pointer to dynamic array with size 3. All unused slots are initialized
        // with default values;
        Radio& setPairs(std::vector <FrqDesc> newPairs);
        std::string getInfo() const;
    };
}

#endif //LAB4_AGENCY_H
