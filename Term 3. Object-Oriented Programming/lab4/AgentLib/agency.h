//
// Created by USER on 07.11.2022.
//

/*!
    \file
    \brief Header with definition of Agency classes

    This file has definitions of parent Agency class and three child classes, which describes three types of agencies.
*/
#ifndef LAB4_AGENCY_H
#define LAB4_AGENCY_H
#include <iostream>
#include <string>
#include <vector>

namespace agencies {
    /// Set of types of agencies
    enum types {
        unnamed = 0, /// Agency has no type - should be only in basic class
        printing = 1, /// type of printed edition agency
        radio = 2, /// type of radio station agency
        telecompany = 3 /// type of television company agency
    };

    /// returns string with name of type of Agency.
    std::string getPrintableType(types type);
    /// returns type of Agency which name of type is inputted.
    types stotypes(const std::string& s);

    std::istream& operator >>(std::istream&, types&);

    /*!
	    \brief Basic Agency class

	    This class is just parent class for agencies, and should really be abstract. The only reason it's not abstract -
        possibility of initialisation of child-class by parent class (in case if some agency distributes
        information in various ways).
    */
    class Agency {
    protected:
        std::string profile, place;
        long long license;
        types type;
        virtual std::ostream& printInfo(std::ostream& os) const;
        virtual std::istream& learnInfo(std::istream& is);
        /*!
            Inner function for == operator's work
            \param secPtr pointer on agency which stays right to operator
            \return true if Agencies (or child objects, if called for them) are equal, false otherwise
        */
        virtual bool isEqual(const Agency* secPtr) const;
    public:
        Agency(std::string prof = "Profile", std::string pl = "Place", const long long &lic = 0,
               const types &typ = unnamed);
        virtual ~Agency() {};
        /// makes copy of object and returns pointer to copy
        virtual Agency *clone() const;
        /// returns string with info about Agency
        virtual std::string getInfo() const;
        types getType() const;
        std::string getProfile() const;
        std::string getPlace() const;
        long long getLicense() const;
        Agency& banLicense();
        friend std::ostream& operator <<(std::ostream& os, const agencies::Agency& src);
        friend std::istream& operator >>(std::istream& is, agencies::Agency& dest);
        friend bool operator ==(const agencies::Agency& first, const agencies::Agency& second);

    };

    /*!
	    \brief Printed edition class

	    This class is child class for Agency, and describes work with information about printed edition agency.
    */
    class Printing: public Agency {
    protected:
        int period, printrun;
        virtual std::ostream& printInfo(std::ostream& os) const;
        virtual std::istream& learnInfo(std::istream& is);
        virtual bool isEqual(const Agency* secPtr) const;
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
    /*!
	    \brief Television company class

	    This class is child class for Agency, and describes work with information about television agency.
    */
    class Telecompany: public Agency {
    protected:
        /// frequency is frequency channel which television company uses for spreading information.
        double frequency;
        virtual std::ostream& printInfo(std::ostream& os) const;
        virtual std::istream& learnInfo(std::istream& is);
        virtual bool isEqual(const Agency* secPtr) const;
    public:
        Telecompany(const double &frq = 1);
        Telecompany(const Agency &ag, const double &frq = 1);
        Telecompany(const std::string &prof, const std::string &pl, const long long &lic, const double &frq = 1);
        virtual Agency *clone() const;
        double getFrequency() const;
        std::string getInfo() const;
    };

    /*!
	    \brief Frequency describer struct

	    This struct holds set of radio characteristics. Frequency describes how often Radio agency spreads information
        in current range.
        [translationFrom; translationTo] is range of frequency channels used by Agency
    */
    struct FrqDesc {
        double frequency, translationFrom, translationTo;
        FrqDesc(const double &frq = 1, const double &from = 1, const double &to = 2);
        friend std::ostream& operator <<(std::ostream&, const FrqDesc& src);
        friend std::istream& operator >>(std::istream&, FrqDesc& dest);
        friend bool operator ==(const FrqDesc& first, const FrqDesc& second);
        friend bool operator !=(const FrqDesc& first, const FrqDesc& second);
    };
    /*!
	    \brief Radio agency class

	    This class is child class for Agency, and describes work with information about radio agency.
    */
    class Radio: public Agency {
    protected:
        /// describes how many frequency sets used by this radio agency (more than 0 and less than 4).
        int amount;
        /*!
            Array of 3 frequency describers used by Radio agency. It's called pairs because each FrqDesc is basically
            pair of frequency and range of frequency channels.
        */
        FrqDesc pairs[3];
        virtual std::ostream& printInfo(std::ostream& os) const;
        virtual std::istream& learnInfo(std::istream& is);
        virtual bool isEqual(const Agency* secPtr) const;
    public:
        Radio(const std::vector <FrqDesc>& newpairs = {});
        Radio(const std::string &prof, const std::string &pl, const long long &lic, const std::vector <FrqDesc> &newpairs = {});
        Radio(const Agency &ag, const std::vector <FrqDesc> &newpairs = {});
        virtual Agency *clone() const;
        std::vector <FrqDesc> getPairs() const;
        Radio& setPairs(std::vector <FrqDesc> newPairs);
        std::string getInfo() const;
    };
}

#endif //LAB4_AGENCY_H
