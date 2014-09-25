/*
 * Account.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: Team 5
 */

#define _CRT_SECURE_NO_WARNINGS

#include "Account.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

	float balance;
	bool initialized;
	string type;
	vector<string> transHist;

/*constructors*/

	/*default constructor*/
	Account::Account() {
		initialized = false;
	}

Account::Account(float bal, string t) {
	balance = bal;
	type = t;
	initialized = true;
}

/*deconstructor */
Account::~Account(void){

}

/*getters & setters*/
/*get the current balance for selected account*/
float Account::getBal(){
	return balance;
}

bool Account::getIni(){
	return initialized;
}


/*deposit money into current account*/
void Account::addBal(float amt){
	balance += amt;
	ostringstream hist;
	hist << "Withdraw of $" << amt << ". Current balance: $" << balance;
	transHist.push_back(hist.str());
}

/*withdraw money from current account*/
void Account::subBal(float amt){
	balance -= amt;
	ostringstream hist;
	if (type == "Chq" && balance < 1000) {
		hist << "Withdraw of $" << amt << " ($2 surcharge included). Current balance: $" << balance;
		transHist.push_back(hist.str());
	}
	else {
		hist << "Withdraw of $" << amt << ". Current balance: $" << balance;
		transHist.push_back(hist.str());
	}
}

/*print out transaction history*/
void Account::history(){
	cout << endl;
	for (int i = 0; i < transHist.size(); i++){
		cout << transHist[i] << endl;
	}
};
