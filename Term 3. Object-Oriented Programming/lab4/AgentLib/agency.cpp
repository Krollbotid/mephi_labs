//
// Created by USER on 07.11.2022.
//

#include "agency.h"
#include <utility>

namespace agencies {
    // types:
    std::string getPrintableType(types type) {
        std::string arr[] = {"unnamed", "printing", "radio", "telecompany"};
        return arr[type];
    }

    types stotypes(const std::string& s) {
        std::string arr[] = {"unnamed", "printing", "radio", "telecompany"};
        for (int i = 1; i < sizeof(arr) / sizeof(arr[0]); i++) {
            if (s == arr[i]) {
                return types(i);
            }
        }
        return unnamed;
    }

    std::istream& operator >>(std::istream& is, types& type) {
        std::string s;
        is >> s;
        type = stotypes(s);
        return is;
    }
    // Agency:
    Agency::Agency(const std::string &prof, const std::string &pl, const long long &lic, const agencies::types &typ) :
        profile(prof), place(pl), license(lic), type(typ) {}

    types Agency::getType() const {
        return type;
    }

    std::string Agency::getProfile() const {
        return profile;
    }

    std::string Agency::getPlace() const {
        return place;
    }

    long long Agency::getLicense() const {
        return license;
    }

    std::string Agency::getInfo() const {
        return "Profile: " + profile + " License: №" + std::to_string(license) + " Place: " + place + " Type: "
        + getPrintableType(type);
    }

    std::ostream& operator <<(std::ostream& os, const Agency& ag) {
        return ag.printInfo(os);
    }

    std::istream& operator >>(std::istream& is, Agency& ag) {
        return ag.learnInfo(is);
    }

    std::ostream &Agency::printInfo(std::ostream &os) const {
        return os;
    }
    std::istream &Agency::learnInfo(std::istream &is) {
        return is;
    }

    bool operator==(const Agency &a, const Agency &b) {
        return a.license == b.license && a.type == b.type && a.place == b.place && a.profile == b.profile;
    }

    // Printing:
    Printing::Printing(const int &per, const int &prtr): Agency(), period(per), printrun(prtr) {
        type = printing;
    }

    Printing::Printing(const std::string& prof, const std::string& pl, const long long &lic, const int &per, const int &prtr):
        Agency(prof, pl, lic, printing), period(per), printrun(prtr) {}

    Printing::Printing(const agencies::Agency &ag, const int &per, const int &prtr): Agency(ag), period(per), printrun(prtr)  {
        type = printing;
    }

    int Printing::getPeriod() const {
        return period;
    }

    int Printing::getPrintrun() const {
        return printrun;
    }

    std::string Printing::getInfo() const {
        return "Profile: " + profile + " License: №" + std::to_string(license) + " Place: " + place + " Type: "
        + getPrintableType(type) + " Period: " + std::to_string(period) + " Printrun: "
        + std::to_string(printrun);
    }

    Printing& Printing::setPeriod(int newPeriod) {
        period = newPeriod;
        return *this;
    }

    Printing& Printing::setPrintrun(int newPrintrun) {
        printrun = newPrintrun;
        return *this;
    }

    std::ostream& Printing::printInfo(std::ostream &os) const {
        return os << this->getInfo();
    }

    std::istream& Printing::learnInfo(std::istream &is) {
        return is >> profile >> license >> place >> type >> period >> printrun;
    }

    bool operator==(const Printing& a, const Printing& b) {
        return a.license == b.license && a.type == b.type && a.place == b.place && a.profile == b.profile
        && a.period == b.period && a.printrun == b.printrun;
    }
    // Telecompany:
    Telecompany::Telecompany(const double &frq): Agency(), frequency(frq) {
        type = telecompany;
    }

    Telecompany::Telecompany(const std::string &prof, const std::string &pl, const long long &lic, const double &frq):
            Agency(prof, pl, lic, telecompany), frequency(frq) {}

    Telecompany::Telecompany(const agencies::Agency &ag, const double &frq): Agency(ag), frequency(frq)  {
        type = telecompany;
    }

    double Telecompany::getFrequency() const {
        return frequency;
    }

    std::string Telecompany::getInfo() const {
        return "Profile: " + profile + " License: №" + std::to_string(license) + " Place: " + place + " Type: "
               + getPrintableType(type) + " Frequency: " + std::to_string(frequency);
    }

    std::ostream& Telecompany::printInfo(std::ostream &os) const {
        return os << this->getInfo();
    }

    std::istream& Telecompany::learnInfo(std::istream &is) {
        return is >> profile >> license >> place >> type >> frequency;
    }

    bool operator==(const Telecompany& a, const Telecompany& b) {
        return a.license == b.license && a.type == b.type && a.place == b.place && a.profile == b.profile
               && a.frequency == b.frequency;
    }

    // FrqDesc:
    FrqDesc::FrqDesc(const double &frq, const double &from, const double &to): frequency(frq), translationFrom(from), translationTo(to) {}

    std::ostream& operator<<(std::ostream &os, const FrqDesc &frq) {
        return os << frq.frequency << " " << frq.translationTo << " " << frq.translationFrom;
    }

    std::istream& operator>>(std::istream &is, FrqDesc &frq) {
        return is >> frq.frequency >> frq.translationTo >> frq.translationFrom;
    }

    bool operator==(const FrqDesc &a, const FrqDesc &b) {
        return a.frequency == b.frequency && a.translationFrom == b.translationFrom && a.translationTo == b.translationTo;
    }

    bool operator!=(const FrqDesc &a, const FrqDesc &b) {
        return !(a == b);
    }

    // Radio:
    Radio::Radio(const std::vector<FrqDesc>& newpairs): Agency() {
        if (newpairs.size() > 3) {
            throw std::range_error("Too many pairs put in constructor");
        }
        for (int i = 0; i < newpairs.size(); i++) {
            pairs[i] = newpairs[i];
        }
        amount = newpairs.size();
        for (int i = newpairs.size(); i < 3; i++) {
            pairs[i] = FrqDesc();
        }
        type = radio;
    }

    Radio::Radio(const std::string &prof, const std::string &pl, const long long &lic, const std::vector<FrqDesc> &newpairs):
        Agency(prof, pl, lic, radio) {
            if (newpairs.size() > 3) {
                throw std::range_error("Too many pairs put in constructor");
            }
            for (int i = 0; i < newpairs.size(); i++) {
                pairs[i] = newpairs[i];
            }
            amount = newpairs.size();
            for (int i = newpairs.size(); i < 3; i++) {
                pairs[i] = FrqDesc();
            }
    }

    Radio::Radio(const Agency &ag, const std::vector<FrqDesc> &newpairs): Agency(ag) {
        if (newpairs.size() > 3) {
            throw std::range_error("Too many pairs put in constructor");
        }
        for (int i = 0; i < newpairs.size(); i++) {
            pairs[i] = newpairs[i];
        }
        amount = newpairs.size();
        for (int i = newpairs.size(); i < 3; i++) {
            pairs[i] = FrqDesc();
        }
        type = radio;
    }

    Radio::Radio(const Radio& r): Agency(r.profile, r.place, r.license, radio), amount(r.amount) {
        for (int i = 0; i < 3; i++) {
            pairs[i] = r.pairs[i];
        }
    }

    Radio::Radio(agencies::Radio &&r) : Radio(r) {}

    std::vector <FrqDesc> Radio::getPairs() const {
        std::vector <FrqDesc> ans;
        for (int i = 0; i < 3; i++) {
            ans.push_back(pairs[i]);
        }
        return ans;
    }

    Radio &Radio::setPairs(std::vector<FrqDesc> newPairs) {
        if (newPairs.size() > 3) {
            throw std::range_error("Too many pairs put in constructor");
        }
        for (int i = 0; i < newPairs.size(); i++) {
            pairs[i] = newPairs[i];
        }
        amount = newPairs.size();
        for (int i = newPairs.size(); i < 3; i++) {
            pairs[i] = FrqDesc();
        }
    }

    std::string Radio::getInfo() const {
        std::string ans = "Profile: " + profile + " License: №" + std::to_string(license) + " Place: " + place + " Type: "
               + getPrintableType(type);
        for (int i = 0; i < amount; i++) {
            ans += " FrqDesc №" + std::to_string(i + 1) + " Frequency: " + std::to_string(pairs[i].frequency)
                    + " Range: From: " + std::to_string(pairs[i].translationFrom) + " To: " +
                    std::to_string(pairs[i].translationTo);
        }
        return ans;
    }

    std::ostream& Radio::printInfo(std::ostream &os) const {
        return os << this->getInfo();
    }

    std::istream& Radio::learnInfo(std::istream &is) {
        is >> profile >> license >> place >> type >> amount;
        if (amount > 3 || amount < 1) {
            throw std::range_error(" amount must be from [1; 3]");
        }
        for (int i = 0; i < amount; i++) {
            is >> pairs[i];
        }
        return is;
    }

    bool operator==(const Radio& a, const Radio& b) {
        if (a.license == b.license && a.type == b.type && a.place == b.place && a.profile == b.profile
               && a.amount == b.amount) {
            for (int i = 0; i < a.amount; i++) {
                if (a.pairs[i] != b.pairs[i]) {
                    return false;
                }
            }
        }
        return true;
    }
}