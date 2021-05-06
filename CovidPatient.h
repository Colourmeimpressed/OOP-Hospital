//Student Name: Adam Springett
//Student ID: 130761209
//Email: aspringett@myseneca.ca
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#ifndef SDDS_COVIDPATIENT_H_
#define SDDS_COVIDPATIENT_H_
#include "IOAble.h"
#include "Patient.h"
namespace sdds
{
	class CovidPatient : public Patient
	{
	public:
		CovidPatient();
		virtual char type() const;
		std::istream& csvRead(std::istream&);
		std::ostream& write(std::ostream&)const;
		std::istream& read(std::istream& istr);
	};
}
#endif // !SDDS_COVIDPATIENT_H_



