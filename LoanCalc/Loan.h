#pragma once

#include <string>

using namespace std;

class Loan
{
public:
	Loan(double, double, int);
	
	double getPrincipal();
	double getInterest();
	double getPmntAmt();
	double getIntAmnt(int);
	double getBegBal(int);
	double getEndBal(int);

	int getMonths();

	bool saveLoan(string);

	~Loan();

private:
	double principal;
	double interest;
	double pmntAmt;

	int months;

	bool vError;

	string vErrorMsg;

	double* bbal;
	double* ebal;
	double* ipay;
};

