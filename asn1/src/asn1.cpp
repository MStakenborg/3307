#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Account.h"
#include "Maint.h"

using namespace std;

int action;


/*open an account - this needs work still .. just put something in for now */
int openAccount(){
	std::string type;
	int initBal;
	int pin;
	cout << "Are you opening a chequing or savings account?\n" << endl;
	cin >> type;
	cout << "Enter a 4 digit PIN number for your new account:\n " << endl;
	cin >> pin;
	cout << "Enter the initial balance for the account\n" << endl;
	cin >> initBal;
	Account acct(initBal, pin, type);
	return 0;
}
/*close an account - delete account from tree*/
int closeAccount(){
	return 0;
}
/*deposit money*/
int deposit(){
	return 0;
}
/*withdrawl money*/
int withdraw() {
	return 0;
}

/*maintenance login*/
int maint() {
	return 0;
}


/*Main program*/
int main() {
	cout << "Enter 0 to open a new account, 1 to close an account, 3 to deposit money, 4 to withdraw money, q for quit or enter login id for maintenance";
	cin >> action;
	switch(action){
	case 1 :
		openAccount();
		break;
	case 2 :
		closeAccount();
		break;
	case 3 :
		deposit();
		break;
	case 4 :
		withdraw();
		break;
	case 5 :
		maint();
		break;
	}
	return 0;
}
