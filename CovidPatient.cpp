//Student Name: Adam Springett
//Student ID: 130761209
//Email: aspringett@myseneca.ca
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#include <iostream>
#include "CovidPatient.h"
namespace sdds
{
	int nextCovidTicket = 1;

	CovidPatient::CovidPatient() : Patient::Patient(nextCovidTicket) {
		nextCovidTicket++;
	}
	
	char CovidPatient::type() const {
		return 'C';
	}

	std::istream& CovidPatient::csvRead(std::istream& istr) {
		Patient::csvRead(istr);
		nextCovidTicket = Patient::number() + 1;
		istr.ignore(1000, '\n');
		return istr;
	}

	std::ostream& CovidPatient::write(std::ostream& ostr)const {
		if (Patient::fileIO()) {
			Patient::csvWrite(ostr);
		}
		else {
			ostr << "COVID TEST\n";
			Patient::write(ostr);
			ostr << std::endl;
		}
		return ostr;
	}

	std::istream& CovidPatient::read(std::istream& istr) {
		if (Patient::fileIO()) {
			csvRead(istr);
		}
		else {
			Patient::read(istr);
		}
		return istr;
	}
}