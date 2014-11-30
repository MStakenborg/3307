/*
* MainMenu.cpp
*
*  Created on: Nov 29, 2014
*      Author: Team 14
*/

#include "Bank.h"
#include "Vendor.h"

using namespace std;

ofstream traceFile;

// user chooses to use the vendor system or the bank system
void selectBankOrVendor(Bank& bank, Vendor& vendor){
	string option;
	cout << "\nWelcome, enter:\n\n 0 to use the bank system\n 1 to use the vendor system\n 2 to trigger end of month event\n q to quit\n\n ";
	cin >> option;
	// bank system
	if (option == "0"){
		traceFile << bank.getTime() << " --- Unknown user chose to use the bank system.\n\n";
		bank.menu(); // access the bank menu
		selectBankOrVendor(bank, vendor);
	}
	// vendor system
	else if (option == "1"){
		traceFile << bank.getTime() << " --- Unknown user chose to use the vendor system.\n\n";
		vendor.menu(); // access the vendor menu
		selectBankOrVendor(bank, vendor);
	}
	// triggers end of month event
	else if (option == "2"){
		traceFile << bank.getTime() << " --- Unknown user chose to use the end of month event.\n\n";
		bank.endOfMonth();
		selectBankOrVendor(bank, vendor);
	}
	// close program
	else if (option == "q"){
		traceFile << bank.getTime() << " --- Unknown user shut down program, execution tracer is turned off.\n";
		traceFile.close();
	}
	// invalid input
	else {
		traceFile << bank.getTime() << " --- Unknown user entered invalid input in the main menu.\n";
		cout << "\nInvalid input\n\n";
		selectBankOrVendor(bank, vendor);
	}
}

int main() {
	traceFile.open("trace.txt", ios::app); // opens the execution trace
	Bank bank = Bank(traceFile); // initializes the bank system
	Vendor vendor = Vendor(traceFile, bank); // initializes the vendor system
	selectBankOrVendor(bank, vendor); // user chooses to use the vendor system or the bank system
	return 0;
}