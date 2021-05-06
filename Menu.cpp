#define _CRT_SECURE_NO_WARNINGS
//Student Name: Adam Springett
//Student ID: 130761209
//Email: aspringett@myseneca.ca
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "utils.h"
namespace sdds
{
	void Menu::setEmpty() {
		m_text = nullptr;
		m_noOfSel = 0;
	}

	void Menu::setText(const char* text) {
		delete[] m_text;
		m_text = nullptr;
		m_text = new char[strlen(text) + 1];
		strcpy(m_text, text);
	}
	
	Menu::Menu(const char* MenuContent, int NoOfSelections) {

		setEmpty();
		m_text = nullptr;
		if (MenuContent != nullptr) {
			setText(MenuContent);
		}
		if (NoOfSelections > 0) {
			m_noOfSel = NoOfSelections;
		}
		else {
			m_noOfSel = 0;
		}
	}

	Menu::~Menu() {
		delete[] m_text;
		m_text = nullptr;
	}

	Menu::Menu(const Menu& src) {
		setEmpty();

		if (src.m_noOfSel > 0) {
			m_noOfSel = src.m_noOfSel;
		}
		if (m_text == nullptr && src.m_text != nullptr) {
			setText(src.m_text);
		}
	}

	void Menu::display()const {
		std::cout << m_text << std::endl;
		std::cout << "0- Exit" << std::endl;
	}

	int& Menu::operator>>(int& Selection) {
		display();
		Selection = getInt(0, m_noOfSel, "> ", "Invalid option ", true);

		return Selection;
	}
}