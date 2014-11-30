/*
* ChqAccount.cpp
*
*  Created on: Nov 29, 2014
*      Author: Team 14
*/

#define _CRT_SECURE_NO_WARNINGS

#include "ChqAccount.h"

using namespace std;

float creditLimit;
float creditDebt;
float outstandingDebt;
vector<string>creditHist;
bool frozen;
bool fullAmount;

/*default constructor*/
ChqAccount::ChqAccount() {
	initialized = false;
}

ChqAccount::ChqAccount(float bal, string t, float initCredit, bool fAmount){
	balance = bal;
	type = t;
	initialized = true;
	creditLimit = initCredit;
	creditDebt = 0;
	outstandingDebt = 0;
	monthlyTotal = 0;
	fullAmount = fAmount;
	frozen = false;
}

/*deconstructor */
ChqAccount::~ChqAccount(void){

}

bool ChqAccount::depositToCredit(float amt){
	if (amt > balance){
		return false;
	}
	else {
		balance -= amt;
		creditDebt -= amt;
		outstandingDebt -= amt;
		if (outstandingDebt <= 0){
			unfreeze();
			outstandingDebt = 0;
		}
		return true;
	}
}

void ChqAccount::applyPayment(float amt){
	creditDebt -= amt;
	ostringstream cHist;
	cHist << "Credit Payment of $" << amt << ". Current Credit Debt: $" << creditDebt;
	creditHist.push_back(cHist.str());
}

bool ChqAccount::payment(float amt){
	if (amt > balance){
		outstandingDebt += amt;
		interest();
		freeze();
		return false;
	}
	else {
		balance -= amt;
		applyPayment(amt);
		if (!fullAmount){
			interest();
		}
		return true;
	}
}

void ChqAccount::interest(){
	creditDebt *= 1.02;
}

void ChqAccount::purchase(float amt){
	creditDebt += amt;
	monthlyTotal += amt;
	ostringstream cHist;
	cHist << "Purchase of $" << amt << ". Current Credit Debt: $" << creditDebt;
	creditHist.push_back(cHist.str());
}

void ChqAccount::creditHistory(){
	cout << endl;
	cout << "\nMonthly credit card purchases: \n";
	if (creditHist.size() == 0){
		cout << "No purchases this month";
	}
	for (int i = 0; i < creditHist.size(); i++){
		cout << creditHist[i] << endl;
	}
	cout << "\nTotal monthly purchases: $\n" << monthlyTotal;
	if (monthlyTotal >(.75 * balance)){
		cout << "\nWARNING: your total monthly purchases exceeds 75% of your balance.\n";
	}

}

void ChqAccount::resetHistory(){
	creditHist.clear();
	monthlyTotal = 0;
}

void ChqAccount::freeze(){
	frozen = true;
}

void ChqAccount::unfreeze(){
	frozen = false;
}

bool ChqAccount::getFreeze(){
	return frozen;
}

bool ChqAccount::getFullAmount(){
	return fullAmount;
}

float ChqAccount::getDebt(){
	return creditDebt;
}

float ChqAccount::getOutstandingDebt(){
	return outstandingDebt;
}