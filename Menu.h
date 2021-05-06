//Student Name: Adam Springett
//Student ID: 130761209
//Email: aspringett@myseneca.ca
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_
#include <iostream>
namespace sdds
{
    class Menu
    {
        char* m_text; // holds the menu content dynamically
        int m_noOfSel;  // holds the number of options displayed in menu content
        void setEmpty();
        void setText(const char* text);
        void display()const;
        Menu& operator=(const Menu&) = delete;
    public:
        Menu(const char* MenuContent, int NoOfSelections);
        virtual ~Menu();
        Menu(const Menu&);
        int& operator>>(int& Selection);
        // add safe copying logic
    };
}
#endif