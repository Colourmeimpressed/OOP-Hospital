//Student Name: Adam Springett
//Student ID: 130761209
//Email: aspringett@myseneca.ca
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#include <iostream>
#include "IOAble.h"
namespace sdds
{
	std::ostream& IOAble::csvWrite(std::ostream& ostr)const {
		return ostr;
	}
	std::istream& IOAble::csvRead(std::istream& istr) {
		return istr;
	}
	std::ostream& IOAble::write(std::ostream& ostr)const {
		return ostr;
	}
	std::istream& IOAble::read(std::istream& istr) {
		return istr;
	}
	IOAble::~IOAble() {}
	std::ostream& operator<<(std::ostream& ostr, const IOAble& ioa) {
		return ioa.write(ostr);
	}
	std::istream& operator>>(std::istream& istr, IOAble& ioa) {
		return ioa.read(istr);
	}
}