#define _CRT_SECURE_NO_WARNINGS
//Student Name: Adam Springett
//Student ID: 130761209
//Email: aspringett@myseneca.ca
//I have done all the coding by myself and only copied the code that my professor
#include <cstring>
#include <fstream>
#include <iostream>
#include "PreTriage.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
namespace sdds
{
	PreTriage::PreTriage(const char* dataFilename) : m_averCovidWait(15), m_averTriageWait(5), m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)  {
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		load();
	}
	
	PreTriage::~PreTriage() {
		std::ofstream file(m_dataFilename);
		std::cout << "Saving Average Wait Times," << std::endl;
		std::cout << "   COVID Test: " << m_averCovidWait << std::endl;
		std::cout << "   Triage: " << m_averTriageWait << std::endl;
		std::cout << "Saving m_lineup..." << std::endl;
		for (int i = 0; i < m_lineupSize; i++) {
			if (i == 0) {
				file << m_averCovidWait << ',' << m_averTriageWait << std::endl;
			}
			m_lineup[i]->fileIO(true);
			file << *m_lineup[i] << std::endl;
			std::cout << i + 1 << "- " << *m_lineup[i] << std::endl;
			delete m_lineup[i];
		}
		delete[] m_dataFilename;
		m_dataFilename = nullptr;
		std::cout << "done!" << std::endl;
	}

	const Time PreTriage::getWaitTime(const Patient& p)const {
		int patientCount = 0;
		for (int i = 0; i < m_lineupSize; i++) {
			if (p.type() == m_lineup[i]->type()) {
				patientCount++;
			}
		}

		return Time(p) *= patientCount;
	}

	void PreTriage::setAverageWaitTime(const Patient& p) {
		Time CT;
		CT.setToNow();
		if (p.type() == 'C') {
			m_averCovidWait = ((CT - Time(p)) + (m_averCovidWait * ((unsigned int)p.number() - 1))) / (unsigned int)p.number();
		}
		if (p.type() == 'T') {
			m_averTriageWait = ((CT - Time(p)) + (m_averTriageWait * ((unsigned int)p.number() - 1))) / (unsigned int)p.number();
		}
	}

	void PreTriage::removePatientFromLineup(int index) {
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const {
		int i, match = -1;

		for (i = 0; i < m_lineupSize; i++) {
			if (m_lineup[i]->type() == type) {
				match = i;
				i = m_lineupSize;
			}
		}
		return match;
	}

	void PreTriage::load() {
		char ch = 'x';
		int count = 0;
		std::ifstream file(m_dataFilename);
		std::cout << "Loading data..." << std::endl;

		if (file) {
			file >> m_averCovidWait;
			file.ignore(1000, ',');
			file >> m_averTriageWait;
			file.ignore(1000, '\n');
			for (int i = 0; file && i < maxNoOfPatients; i++) {
				Patient* patient = nullptr;
				ch = file.get();
				file.ignore(1000, ',');
				if (ch == 'C') {
					patient = new CovidPatient();
				}
				else if (ch == 'T') {
					patient = new TriagePatient();
				}
				if (patient) {
					count++;
					patient->fileIO(true);
					patient->csvRead(file);
					patient->fileIO(false);
					m_lineup[i] = patient;
					m_lineupSize++;
					patient = nullptr;
				}
			}
		}
		if (count - maxNoOfPatients >= 0) {
			std::cout << "Warning: number of records exceeded 100" << std::endl;
		}
		if (count == 0) {
			std::cout << "No data or bad data file!" << std::endl;
		}
		else {
			std::cout << m_lineupSize << " Records imported..." << std::endl;
		}
		std::cout << std::endl;
		
	}

	void PreTriage::reg() {
		int selection;

		if (m_lineupSize == maxNoOfPatients) {
			std::cout << "Line up full!" << std::endl;
		}
		else {
			m_pMenu >> selection;

			switch (selection) {
			case 1:
				m_lineup[m_lineupSize] = new CovidPatient();
				break;
			case 2:
				m_lineup[m_lineupSize] = new TriagePatient();
				break;
			case 0:
				break;


			}

			m_lineup[m_lineupSize]->setArrivalTime();
			m_lineup[m_lineupSize]->fileIO(false);
			std::cout << "Please enter patient information: " << std::endl;
			std::cin >> *m_lineup[m_lineupSize];
			std::cout << std::endl;
			std::cout << "******************************************" << std::endl;
			std::cout << *m_lineup[m_lineupSize];
			std::cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << std::endl;
			std::cout << "******************************************" << std::endl << std::endl;
			m_lineupSize++;
		}
	}

	void PreTriage::admit() {
		int selection, firstInLineIndex;
		char type = '\0';
		m_pMenu >> selection;
		std::cout << std::endl;

		switch (selection) {
		case 1:
			type = 'C';
			break;
		case 2:
			type = 'T';
			break;
		case 0:
			break;
		}

		firstInLineIndex = indexOfFirstInLine(type);
		if (firstInLineIndex != -1) {
			std::cout << "******************************************" << std::endl;
			m_lineup[firstInLineIndex]->fileIO(false);
			std::cout << "Calling for " << *m_lineup[firstInLineIndex];
			std::cout << "******************************************" << std::endl << std::endl;
			setAverageWaitTime(*m_lineup[firstInLineIndex]);
			removePatientFromLineup(firstInLineIndex);
		}
	}

	void PreTriage::run() {
		int selection;
		bool repeat = true;

		while (repeat) {
			m_appMenu >> selection;
			switch (selection) {
			case 1:
				reg();
				break;
			case 2:
				admit();
				break;
			case 0:
				repeat = false;
				break;
			}
		}
	}
}
