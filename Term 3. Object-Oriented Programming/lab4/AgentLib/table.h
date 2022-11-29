//
// Created by USER on 22.11.2022.
//

#ifndef LAB4_TABLE_H
#define LAB4_TABLE_H

#include "agency.h"
#include <map>

using namespace agencies;

namespace table {
    std::ostream &operator<<(std::ostream &, const std::pair <const std::string, Agency * > &);
    std::string printPair(const std::pair <const std::string, Agency* > &p);

    class ConstTableIt {
    private:
        std::map<const std::string, Agency *>::const_iterator cur;
    public:
        ConstTableIt();
        ConstTableIt(std::map <const std::string, Agency * >::iterator);
        ConstTableIt(std::map <const std::string, Agency * >::const_iterator);
        int operator !=(const ConstTableIt &) const;
        int operator ==(const ConstTableIt &) const;
        const std::pair <const std::string, Agency * > & operator *();
        const std::pair <const std::string, Agency * > * operator ->();
        ConstTableIt & operator ++();
        const ConstTableIt operator ++(int);

    };

    class Table {
    private:
        std::map <const std::string, Agency * > agencies;
    public:
        Table() {};
        Table(const Table &);
        Table &operator=(const Table &);
        ~Table();
        friend class ConstTableIt;
        typedef ConstTableIt Const_Iterator;
        Const_Iterator find(const std::string&) const;
        Table& insert(const std::string &, const Agency *);
        Table& remove(const std::string &);
        std::string printTable() const;
        Const_Iterator begin() const;
        Const_Iterator end() const;
    };

    std::ostream &operator<<(std::ostream &, const Table &);
}


#endif //LAB4_TABLE_H
