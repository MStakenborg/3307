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

// initialize cheqeuing account
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

// credit card payment (not end of month event)
bool ChqAccount::depositToCredit(float amt){
	// if there isn't enough money
	if (amt > balance){
		return false;
	}
	// if there is enough money
	else {
		balance -= amt; // subtract from balance
		creditDebt -= amt; // subtract from debt
		outstandingDebt -= amt; // subtract from outstanding debt
		// if there is no more outstanding debt, unfreeze credit card
		if (outstandingDebt <= 0){
			unfreeze();
			outstandingDebt = 0;
		}
		return true;
	}
}

// makes payment
void ChqAccount::applyPayment(float amt){
	creditDebt -= amt; // reduces credit debt
	ostringstream cHist; // records payment
	cHist << "Credit Payment of $" << amt << ". Current Credit Debt: $" << creditDebt;
	creditHist.push_back(cHist.str());
}

// pay credit card (end of month event)
bool ChqAccount::payment(float amt){
	resetHistory(); // reset monthly history
	// if there are insufficient funds
	if (amt > balance){
		outstandingDebt += amt; // add to outstanding debt
		interest(); // apply interest
		freeze(); // freeze credit card
		return false;
	}
	// payment successfully paid
	else {
		balance -= amt; // subtract from balance
		applyPayment(amt); // apply the payment
		// if it was a minimal payment, apply interest to leftover debt
		if (!fullAmount){
			interest();
		}
		return true;
	}
}

// applies interest to debt
void ChqAccount::interest(){
	creditDebt *= 1.02;
}

// handles a purchase
void ChqAccount::purchase(float amt){
	creditDebt += amt; // adds to the debt
	monthlyTotal += amt; // adds to the monthly total
	ostringstream cHist; // store purchase
	cHist << "Purchase of $" << amt << ". Current Credit Debt: $" << creditDebt;
	creditHist.push_back(cHist.str());
}

// outputs the credit card purchase history
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

// resets the monthly credit card purchase history
void ChqAccount::resetHistory(){
	creditHist.clear();
	monthlyTotal = 0;
}

// freeze the credit card
void ChqAccount::freeze(){
	frozen = true;
}

// unfreeze the credit card
void ChqAccount::unfreeze(){
	frozen = false;
}

// returns status of credit card (frozen or not)
bool ChqAccount::getFreeze(){
	return frozen;
}

// returns true if the credit card payments are paid in full
// returns false if the credit card payments are paid the minimal value
bool ChqAccount::getFullAmount(){
	return fullAmount;
}

// returns creditDebt
float ChqAccount::getDebt(){
	return creditDebt;
}

float ChqAccount::getOutstandingDebt(){
	return outstandingDebt;
}