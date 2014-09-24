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

using namespace std;

	float balance;
	bool initialized;
	string type;

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
}

/*withdraw money from current account, surcharge if over 1000 and error if insufficient funds*/
void Account::subBal(float amt){
	balance -= amt;
};
