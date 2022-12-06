//
// Created by USER on 22.11.2022.
//

/*!
    \file
    \brief Header with definition of Table classes

    This file has definitions of Table class which represents table of Agency and iterator for this table.
*/
#ifndef LAB4_TABLE_H
#define LAB4_TABLE_H

#include "agency.h"
#include <map>


namespace tables {
    std::ostream &operator<<(std::ostream &, const std::pair <const std::string, agencies::Agency * > &);
    /// returns string of Agency's name and info about it.
    std::string printPair(const std::pair <const std::string, agencies::Agency* > &p);

    /*!
	    \brief Iterator-class for Table Class.

	    This class is implemented to make easier work with Table class.
        It supports basic operations for work with dictionary by iterator.
    */
    class ConstTableIt {
    private:
        std::map<const std::string, agencies::Agency *>::const_iterator cur;
    public:
        ConstTableIt();
        ConstTableIt(std::map <const std::string, agencies::Agency * >::iterator);
        ConstTableIt(std::map <const std::string, agencies::Agency * >::const_iterator);
        int operator !=(const ConstTableIt &) const;
        int operator ==(const ConstTableIt &) const;
        const std::pair <const std::string, agencies::Agency * > & operator *();
        const std::pair <const std::string, agencies::Agency * > * operator ->();
        ConstTableIt & operator ++();
        const ConstTableIt operator ++(int);

    };

    /*!
	    \brief This Class is Table of Agencies.

	    Class is dictionary of agencies, made by map of std::string and Agency*.
        You can work with it by iterator class.
    */

    class Table {
    private:
        std::map <const std::string, agencies::Agency * > agencies;
    public:
        Table() {};
        Table(const Table &);
        Table &operator=(const Table &);
        ~Table();
        friend class ConstTableIt;
        typedef ConstTableIt Const_Iterator;
        Const_Iterator find(const std::string&) const;
        /*!
	        \brief insert into table

	        \param [in] s - name of inserting Agency.
            \param [in] ag - reference to inserting Agency.
            \return true if successfully inserted, false if there already is Agency with that name.
        */
        bool insert(const std::string &s, const agencies::Agency &ag);
        /*!
	        \brief replace Agency in table

	        \param [in] s - name of replacing Agency.
            \param [in] ag - reference to new Agency.
            \return true if successfully replaced, false if there already is Agency with that name.
        */
        bool replace(const std::string &s, const agencies::Agency &ag);
        /*!
	        \brief remove from table

	        \param [in] s - name of removing Agency.
            \return true if successfully removed, false if there is no Agency with that name.
        */
        bool remove(const std::string &s);
        /// returns string with full information about table.
        std::string printTable() const;
        Const_Iterator begin() const;
        Const_Iterator end() const;
    };

    std::ostream &operator<<(std::ostream &, const Table &);
}


#endif //LAB4_TABLE_H
