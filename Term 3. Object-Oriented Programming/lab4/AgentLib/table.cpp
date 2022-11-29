//
// Created by USER on 22.11.2022.
//

#include "table.h"
#include <utility>
#include <algorithm>

using namespace agencies;

namespace table {

    std::ostream& operator <<(std::ostream& os, const std::pair <const std::string, agencies::Agency* > &p) {
        return os << "Name: " << p.first << " " << (*p.second);
    }

    std::string printPair(const std::pair <const std::string, Agency* > &p) {
        std::string s = "Name: " + p.first + " " + p.second->getInfo();
        return s;
    }
    //Table

    Table::Table(const Table &a) {
        std::map<const std::string, Agency *>::const_iterator p;
        for (p = a.agencies.begin(); p != a.agencies.end(); ++p)
            agencies.insert(std::make_pair(p->first, p->second->clone()));
    }

    Table::~Table() {
        std::map<const std::string, Agency *>::iterator p;
        try {
            for (p = agencies.begin(); p != agencies.end(); ++p) {
                delete p->second;
                p->second = nullptr;
            }
        } catch (std::exception& ex) {
            throw ex;
        }
    }

    Table& Table::operator = (const Table &a) {
        std::map<const std::string, Agency *>::iterator p;
        if (this != &a){
            try {
                for (p = agencies.begin(); p != agencies.end(); ++p) {
                    delete p->second;
                }
            } catch (std::exception& ex) {
                throw ex;
            }
            agencies.clear();
            std::map<const std::string, Agency *>::const_iterator pp;
            for (pp = a.agencies.begin(); pp != a.agencies.end(); ++pp)
                agencies.insert(std::make_pair(pp->first, pp->second->clone()));
        }
        return *this;
    }

    Table& Table::insert(const std::string &s, const Agency *f) {
        auto p = agencies.find(s);
        if (p == agencies.end()) {
            std::pair<std::map<const std::string, Agency *>::iterator, bool> pp =
                    agencies.insert(std::make_pair(s, f->clone()));
            if (!pp.second)
                throw std::range_error("can't insert new item into map");
        }
        return *this;
    }

    Table& Table::remove(const std::string &s) {
        auto p = agencies.find(s); //agencies.erase(s);
        if (p != agencies.end()){
            delete p->second;
            p->second = nullptr;
            agencies.erase(p);
        }
        return *this;
    }

    Table::Const_Iterator Table::find(const std::string &s) const {
        auto p = agencies.find(s);
        return ConstTableIt(p);
    }

    Table::Const_Iterator Table::begin() const {
        return ConstTableIt(agencies.begin());
    }

    Table::Const_Iterator Table::end() const {
        return ConstTableIt(agencies.end());
    }

    std::string Table::printTable() const {
        std::string ans;
        for (const auto & i : *this) {
            ans += printPair(i) + "\n";
        }
        return ans;
    }
    std::ostream & operator<<(std::ostream& os, const Table& table) {
        Table::Const_Iterator it;
        for(it = table.begin(); it != table.end(); ++it)
            os << (*it) << std::endl;
        return os;
    }

    // Iterator:
    ConstTableIt::ConstTableIt() = default;

    ConstTableIt::ConstTableIt(std::map<const std::string, Agency *>::iterator it): cur(it) {}

    ConstTableIt::ConstTableIt(std::map<const std::string, Agency *>::const_iterator it): cur(it) {}

    int Table::Const_Iterator::operator !=(const ConstTableIt &it) const {
        return cur != it.cur;
    }

    int ConstTableIt::operator ==(const ConstTableIt &it) const {
        return cur == it.cur;
    }

    const std::pair<const std::string, Agency *> & ConstTableIt::operator *() {
        return *cur;
    }

    const std::pair<const std::string, Agency *> * ConstTableIt::operator ->() {
        return &*cur;
    }

    ConstTableIt & ConstTableIt::operator ++() {
        ++cur;
        return *this;
    }

    const ConstTableIt ConstTableIt::operator ++(int) {
        ConstTableIt res(*this);
        ++cur;
        return res;
    }
}