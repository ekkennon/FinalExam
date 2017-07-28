#include "stdafx.h"
#include "Loan.h"
#include <math.h>
#include <fstream>

Loan::Loan(double princ, double rate, int term)
{
	principal = princ;
	interest = rate;
	months = term;

	pmntAmt = ((interest + (interest / ((pow((1 + interest), months)) - 1))) * principal);

	bbal = new double[months];
	ebal = new double[months];
	ipay = new double[months];

	bbal[0] = principal;
	for (int i = 0; i < months; i++) {
		if (i > 0) {
			bbal[i] = ebal[i - 1];
		}
		ebal[i] = bbal[i] - pmntAmt;
		ipay[i] = rate * bbal[i];
	}
}

double Loan::getPrincipal()
{
	return principal;
}

double Loan::getInterest()
{
	return interest * 100;
}

double Loan::getPmntAmt()
{
	return pmntAmt;
}

int Loan::getMonths()
{
	return months;
}

double Loan::getBegBal(int month) {
	return bbal[month - 1];
}

double Loan::getEndBal(int month)
{
	return ebal[month - 1];
}

double Loan::getIntAmnt(int month)
{
	return ipay[month - 1];
}

bool Loan::saveLoan(string filename)
{
	vError = false;
	vErrorMsg = "";
	ofstream fout;

	fout.open(filename);
	if (fout.is_open()) {
		fout << principal << endl;
		fout << interest << endl;
		fout << months << endl;
		fout << pmntAmt << endl;
		fout.close();
		return true;
	}
	else {
		vError = true;
		vErrorMsg = "Unable to write file.";
		return false;
	}
}

Loan::~Loan()
{
}
