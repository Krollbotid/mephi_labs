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
    Agency::Agency(std::string prof, std::string pl, const long long lic, const agencies::types typ) :
        profile(std::move(prof)), place(std::move(pl)), license(lic), type(typ) {}

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

    // Printing:
    Printing::Printing(int per, int prtr): Agency(), period(per), printrun(prtr) {}

    Printing::Printing(std::string prof, std::string pl, long long lic, agencies::types typ, int per, int prtr):
        Agency(std::move(prof), std::move(pl), lic, typ), period(per), printrun(prtr) {}

    Printing::Printing(agencies::Agency &ag, int per, int prtr): Agency(std::move(ag)), period(per), printrun(prtr)  {}

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
    // Telecompany:
    Telecompany::Telecompany(double frq): Agency(), frequency(frq) {}

    Telecompany::Telecompany(std::string prof, std::string pl, long long lic, agencies::types typ, double frq):
            Agency(std::move(prof), std::move(pl), lic, typ), frequency(frq) {}

    Telecompany::Telecompany(agencies::Agency &ag, double frq): Agency(std::move(ag)), frequency(frq)  {}

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
    // FrqDesc:
    FrqDesc::FrqDesc(double frq, double from, double to): frequency(frq), translationFrom(from), translationTo(to) {}

    std::ostream& operator<<(std::ostream &os, const FrqDesc &frq) {
        return os << frq.frequency << " " << frq.translationTo << " " << frq.translationFrom;
    }

    std::istream& operator>>(std::istream &is, FrqDesc &frq) {
        return is >> frq.frequency >> frq.translationTo >> frq.translationFrom;
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
    }

    Radio::Radio(std::string prof, std::string pl, long long lic, agencies::types typ, std::vector<FrqDesc> newpairs):
        Agency(std::move(prof), std::move(pl), lic, typ) {
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

    Radio::Radio(Agency &ag, std::vector<FrqDesc> newpairs): Agency(std::move(ag)) {
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

    FrqDesc *Radio::getPairs() const {
        try {
            FrqDesc *ans = new FrqDesc[3];
            for (int i = 0; i < 3; i++) {
                ans[i] = pairs[i];
            }
            return ans;
        } catch(std::bad_alloc &ex) {
            throw std::bad_alloc(ex);
        }
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
}