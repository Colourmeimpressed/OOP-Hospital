//Student Name: Adam Springett
//Student ID: 130761209
//Email: aspringett@myseneca.ca
//I have done all the coding by myself and only copied the code that my professor
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include "Patient.h"
#include "utils.h"
namespace sdds
{
	Patient::Patient(int ticketNum, bool IOflag) : m_ticket(ticketNum), m_fileCheck(IOflag) {
		m_name = nullptr;
		m_ohipNum = 0;
	}

	Patient::~Patient() {
		delete[] m_name;
		m_name = nullptr;
	}
	
	bool Patient::fileIO()const {
		return m_fileCheck;
	}

	void Patient::fileIO(bool fileCheck) {
		m_fileCheck = fileCheck;
	}

	bool Patient::operator ==(const char matchCheck)const {
		bool match = false;
		if (this->type() == matchCheck) {
			match = true;
		}
		return match;
	}

	bool Patient::operator ==(const Patient& patient)const {
		bool match = false;
		if (this->type() == patient.type()) {
			match = true;
		}
		return match;
	}

	void Patient::setArrivalTime() {
		m_ticket.resetTime();
	}

	Patient::operator Time()const {
		return (Time)m_ticket;
	}

	int Patient::number()const {
		return m_ticket.number();
	}

	std::ostream& Patient::csvWrite(std::ostream& ostr)const {
		ostr << type() << ',' << m_name << ',' << m_ohipNum << ',';
		return m_ticket.csvWrite(ostr);
	}

	std::istream& Patient::csvRead(std::istream& istr) {
		char name[101]{};
		istr.get(name, 101, ',');
		delete[] m_name;
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
		istr.ignore(1000, ',');
		istr >> m_ohipNum;
		istr.ignore();
		return m_ticket.csvRead(istr);
	}

	std::ostream& Patient::write(std::ostream& ostr)const {
		ostr << "Ticket No: " << m_ticket.number() << ", Issued at: " << Time(*this) << std::endl;
		for (int i = 0; i < 25; i++) {
			if (m_name[i] != '\0') {
				ostr << m_name[i];
			}
			else {
				i = 26;
			}
		}
		ostr << ", OHIP: " << m_ohipNum;
		return ostr;

	}

	std::istream& Patient::read(std::istream& istr) {
		delete[] m_name;
		m_name = getcstr("Name: ", istr, '\n');
		m_ohipNum = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ", true);
		return istr;

	}
}