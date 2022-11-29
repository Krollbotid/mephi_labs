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
    Agency::Agency(std::string prof, std::string pl, const long long &lic, const agencies::types &typ) :
        profile(std::move(prof)), place(std::move(pl)), license(lic), type(typ) {}

    Agency *Agency::clone() const {
        return new Agency(*this);
    }

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

    bool Agency::isEqual(const agencies::Agency *b) const {
        return license == b->license && type == b->type && place == b->place && profile == b->profile;
    }

    bool operator==(const Agency &a, const Agency &b) {
        return a.isEqual(&b);
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

    Agency *Printing::clone() const {
        return new Printing(*this);
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

    bool Printing::isEqual(const agencies::Agency *b) const {
        return Agency::isEqual(b) && ((Printing*) b)->period == period && ((Printing*) b)->printrun == printrun;
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

    Agency *Telecompany::clone() const {
        return new Telecompany(*this);
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

    bool Telecompany::isEqual(const agencies::Agency *b) const {
        return Agency::isEqual(b) && ((Telecompany*) b)->frequency == frequency;
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

    Agency *Radio::clone() const {
        return new Radio(*this);
    }

    std::vector <FrqDesc> Radio::getPairs() const {
        std::vector <FrqDesc> ans;
        for (const auto & pair : pairs) {
            ans.push_back(pair);
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
        return *this;
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

    bool Radio::isEqual(const agencies::Agency *b) const {
        if (Agency::isEqual(b) && ((Radio*) b)->amount == amount) {
            for (int i = 0; i < amount; i++) {
                if (pairs[i] != ((Radio*) b)->pairs[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
}