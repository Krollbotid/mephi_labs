//
// Created by USER on 22.11.2022.
//

#include "table.h"
#include <utility>

using namespace agencies;

namespace table {
    std::ostream& operator <<(std::ostream& os, std::pair <std::string, Agency* > &p) {
        return os << "Name " << p.first << " " << (*p.second);
    }

    Table &Table::addAgency(const std::string &, const agencies::Agency *) {
        agencies.
    }
}