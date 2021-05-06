//Student Name: Adam Springett
//Student ID: 130761209
//Email: aspringett@myseneca.ca
//I have done all the coding by myself and only copied the code that my professor
#include "Ticket.h"
namespace sdds
{
    Ticket::Ticket(int number) {
        m_number = number;
    }
    Ticket::operator Time() const {
        return m_time;
    }
    int Ticket::number() const {
        return m_number;
    }
    void Ticket::resetTime() {
        m_time.setToNow();
    }
    std::ostream& Ticket::csvWrite(std::ostream& ostr) const {
        return ostr << m_number << "," << m_time;
    }
    std::istream& Ticket::csvRead(std::istream& istr) {
        istr >> m_number;
        istr.ignore();
        return istr >> m_time;
    }
    std::ostream& Ticket::write(std::ostream& ostr) const {
        return ostr << "Ticket No: " << m_number << ", Issued at: " << m_time;
    }
    std::istream& Ticket::read(std::istream& istr) {
        return csvRead(istr);
    }
}
