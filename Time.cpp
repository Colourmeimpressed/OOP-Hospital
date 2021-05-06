//Student Name: Adam Springett
//Student ID: 130761209
//Email: aspringett@myseneca.ca
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#include "Time.h"
#include "utils.h"
#include <iomanip>
using namespace std;
namespace sdds
{
	Time& Time::setToNow() {

		m_min = getTime();

		return *this;
	}

	Time::Time(unsigned int minutes) {
		m_min = minutes;
	}

	std::ostream& Time::write(std::ostream& ostr) const {
		ostr << setfill('0') << setw(2) << right << m_min / 60 << ":" << setw(2) << m_min % 60;
		return ostr;
	}

	std::istream& Time::read(std::istream& istr) {
		int hour = 0, min = 0;
		char colon = 'x';

		istr >> hour >> colon;
		if (colon != ':' || hour < 0) {
			istr.setstate(ios::failbit);
		}
		else {
			istr >> min;
			if (min < 0) {
				istr.setstate(ios::failbit);
			}
			else {
				m_min = hour * 60 + min;
			}
		}
		return istr;
	}

	Time& Time::operator-=(const Time& D) {
		while (D.m_min > m_min) {
			m_min += 24 * 60;
		}
		m_min -= D.m_min;
		return *this;
	}

	Time Time::operator-(const Time& D)const {
		Time temp = *this;
		temp -= D.m_min;
		return temp;
	}

	Time& Time::operator+=(const Time& D) {
		m_min += D.m_min;
		return *this;
	}

	Time Time::operator+(const Time& D)const {
		Time temp = *this;
		temp += D.m_min;

		return temp;
	}

	Time& Time::operator=(unsigned int val) {
		m_min = val;
		return *this;
	}

	Time& Time::operator *= (unsigned int val) {
		m_min *= val;
		return *this;
	}

	Time& Time::operator /= (unsigned int val) {
		m_min /= val;
		return *this;
	}

	Time Time::operator *(unsigned int val)const {
		Time temp = *this;
		temp *= val;
		return temp;
	}

	Time Time::operator /(unsigned int val)const {
		Time temp = *this;
		temp /= val;
		return temp;
	}

	Time::operator unsigned int()const {
		return m_min;
	}

	Time::operator int()const {
		return m_min;
	}

	std::ostream& operator<<(std::ostream& ostr, const Time& D) {
		return D.write(ostr);
	}

	std::istream& operator>>(std::istream& istr, Time& D) {
		return D.read(istr);
	}

}