//
// Created by USER on 22.11.2022.
//

#ifndef LAB4_TABLE_H
#define LAB4_TABLE_H

#include "agency.h"

using namespace agencies;

namespace table {
    std::ostream& operator <<(std::ostream&, std::pair <std::string, Agency* > &);

    class Table {
    private:
        std::vector <std::pair <std::string, Agency* > > agencies;
    public:
        Table& addAgency(const std::string&, const Agency*);
        Table& removeAgency(const std::string&);
        std::pair <std::string, Agency* > findAgency(const std::string&);
        std::ostream & printTable() const;
    };
}

#endif //LAB4_TABLE_H
