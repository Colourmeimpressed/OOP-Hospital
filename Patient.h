//Student Name: Adam Springett
//Student ID: 130761209
//Email: aspringett@myseneca.ca
//I have done all the coding by myself and only copied the code that my professor
#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
namespace sdds
{
	class Patient : public IOAble
	{
		char* m_name = nullptr;
		int m_ohipNum = 0;
		Ticket m_ticket;
		bool m_fileCheck;
	public:
		Patient(int ticketNum = 0, bool IOflag = false);
		Patient(const Patient&) = delete;
		Patient& operator=(const Patient&) = delete;
		~Patient();
		char virtual type()const = 0;
		bool fileIO()const;
		void fileIO(bool);
		bool operator ==(const char)const;
		bool operator ==(const Patient&)const;
		void setArrivalTime();
		operator Time()const;
		int number()const;
		std::ostream& csvWrite(std::ostream&)const;
		std::istream& csvRead(std::istream&);
		std::ostream& write(std::ostream&)const;
		std::istream& read(std::istream&);
	};
}
#endif