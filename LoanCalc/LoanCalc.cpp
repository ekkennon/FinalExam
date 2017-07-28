// LoanCalc.cpp : main project file.  Erin K Kennon

#include "stdafx.h"
#include "Loan.h"
#include <iostream>
#include <string>

using namespace std;
using namespace System;

double getPrincipal();
double getRate();
int getTerm();
bool getBool(string);
string getFilename();
void printAmorit(Loan);

int main()
{
	cout << "Welcome: this program calculates monthly payments based on principal, interest and term values." << endl << endl;

	double principal = getPrincipal();
	while (principal > 0) {
		double rate = getRate();
		int term = getTerm();

		Loan loan = Loan(principal, rate, term);

		cout << "\nA monthly payment of $" << loan.getPmntAmt() << " is required to pay off a $" << loan.getPrincipal() << " loan in " << loan.getMonths() << " months at a " << loan.getInterest() << "% rate." << endl;

		bool amoritize = getBool("Would you like to see the amortization schedule (Y/N)? ");
		if (amoritize) {
			printAmorit(loan);
		}

		bool save = getBool("Save loan scenario? (Y/N): ");
		if (save) {
			string filename = getFilename();
			if (loan.saveLoan(filename)) {
				cout << "Loan scenario has been saved in file " << filename;
			}
			else {
				cout << "There was an error saving your file.";
			}
		}

		cout << endl;
		principal = getPrincipal();
	}

	cout << endl << "Thanks for using the Payment Calculator!" << endl;
	system("Pause");
    return 0;
}

double getPrincipal() {
	double p;

	do {
		cout << "Please enter your Principal amount (no commas, 0 to Quit): ";
		cin >> p;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Your data was bad so I could not read your input as a decimal value." << endl;
			p = -1;
		}
		else if (p < 0) {
			cout << "Please enter a positive value." << endl;
		}

	} while (p < 0);

	return p;
}

double getRate() {
	double r;

	do {
		cout << "Please enter your Annual Interest Rate (.06 = 6%): ";
		cin >> r;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Your data was bad so I could not read your input as a decimal value." << endl;
			r = -1;
		}
		else if (r < 0) {
			cout << "Please enter a positive value." << endl;
		}
		else if (r > .25) {
			cout << "Interest rate must not be more than 25%";
			r = -1;
		}

	} while (r < 0);

	return r;
}

int getTerm() {
	int m;

	do {
		cout << "Please enter your Term (in months): ";
		cin >> m;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Your data was bad so I could not read your input as a decimal value." << endl;
			m = 0;
		}
		else if (m < 1) {
			cout << "Please enter a positive value." << endl;
		}

	} while (m < 1);

	return m;
}

bool getBool(string message) {
	char choice;
	cout << message;
	cin >> choice;

	if (!cin.good()) {
		cin.clear();
		cin.ignore(1000, '\n');
		choice = 'n';
	}

	if (choice == 'y' || choice == 'Y') {
		return true;
	}
	return false;
};

string getFilename() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string filename;

	cout << "File Name: ";
	getline(cin, filename);

	return filename;
}

void printAmorit(Loan l) {
	cout << " Month | Beginning Principal | Payment | Interest | Ending Principal" << endl;
	for (int i = 1; i < l.getMonths() + 1; i++) {
		cout << "   " << i << "\t\t" << l.getBegBal(i) << "\t\t" << l.getPmntAmt() << "\t" << l.getIntAmnt(i) << "\t\t" << l.getEndBal(i) << endl;

	}
}
