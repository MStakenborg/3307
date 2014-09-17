/*
 * Account.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: Sparky
 */

#include "Account.h"
#include <iostream>
#include <string>

using namespace std;

	float balance;
	int acctId;
	std::string type;
	int pin;
	int idTally = 0;

/*constructor*/
Account::Account(float bal, int pinNum, std::string accType) {
	balance = bal;
	pin = pinNum;
	type = accType;
	acctId = idTally; /// we should change this .. just a placeholder
	idTally++;
}

/*deconstructor */
Account::~Account(void){

}

/*get the current balance for selected account*/
float getBal(){
	return balance;
}

/*deposit money into current account*/
void addBal(float amt){
	balance = balance + amt;
}

/*withdraw money from current account, surcharge if over 1000 and error if insufficient funds*/
void subBal(float amt){
	float checkBal = balance;
	char ans;
	if((checkBal - amt) < balance){
		cout << "There is insufficient funds to process this transaction. Request Denied";
	}
	if((checkBal - amt) < 1000 ){
		cout << "Your balance after withdraw will be less than 1000 and subject to a $2.00 charge. Press Y to continue or any other key to cancel request: Y/N?";
		cin >> ans;
		if (ans = 'Y' || 'y'){
			balance = (balance - amt - 2);
		}
	}
	else {
		balance = balance - amt;
	}
};
