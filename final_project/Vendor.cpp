/*
* Vendor.h
*
*  Created on: Nov 29, 2014
*      Author: Team 14
*/

#include "Vendor.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

vector<string> purchHistory; // purchase history

// default constructor - initializes trace and bank
Vendor::Vendor(std::ofstream& trace, Bank& b) : traceFile(trace), bank(b){
	randomInit(); // sets srand for random number generator
}

// sets srand for random number generator
void Vendor::randomInit(){
	srand(time(NULL));
}

// handles a purchase made
void Vendor::handlePurchase(int i, float amt, string userID){
	// stores the purchase in vendor system history
	ostringstream history; 
	history << userID << " purchased a $" << setprecision(3) << amt << " item.";
	purchHistory.push_back(history.str());
	traceFile << bank.getTime() << " --- purchase record stored in vendor database.\n";
	traceFile << bank.getTime() << " --- purchase sent to bank system.\n\n";
	// sends the purchase to the bank system where it handles it
	bank.handlePurchase(i, amt, history.str());
}

// user accepts or rejects the purchase of an item
void Vendor::purchase(int i){
	int randInt;
	float randFloat;
	string opt;
	randInt = rand() % 9899 + 100; // random int between 100 and 10000
	randFloat = (randInt / 100.0); // random float between 1.00 and 100.00
	
	// the client that is logged in
	Client *client = &bank.getClientList()[i];
	ChqAccount chequing = (*client).getChq();

	// if the number is greater than 10, set precision to 4 (to output 2 decimal places)
	int prec = 3;
	if (randFloat >= 10){
		prec = 4;
	}

	cout << "\nThe item for sale costs $" << setprecision(prec) << randFloat;
	cout << "\nEnter:\n\n 0 to buy the item\n 1 to reject the item\n\n";
	cin >> opt; // user input to buy or reject
	// user buys item
	if (opt == "0"){
		// if the credit card is frozen
		if (chequing.getFreeze()){
			traceFile << "\n" << bank.getTime() << " --- " << (*client).getId() << " chose to purchase the $" << setprecision(prec)
				<< randFloat << " item but their credit card is frozen. User is logged out of vendor system\n";
			traceFile << "\n" << bank.getTime() << " --- " << " client notification sent to bank system.\n\n";
			cout << "\nTransaction cancled, your credit card is frozen\n";
			bank.notifyClient(i, randFloat); // notify the client that the purchase didn't go through
			menu(); // log out of vendor system
		}
		// the credit card isn't frozen, complete the purchase
		else {
			traceFile << bank.getTime() << " --- " << (*client).getId() << " chose to purchase the $" 
				<< setprecision(prec) << randFloat << " item. User is logged out of vendor system\n\n";
			handlePurchase(i, randFloat, (*client).getId()); // complete the purchase
			menu(); // log out of vendor system
		}
	}
	// if the user rejects the purchase
	else if (opt == "1"){
		traceFile << bank.getTime() << " --- " << (*client).getId() << " chose to reject the $" 
			<< setprecision(prec) << randFloat << " item. User is logged out of vendor system\n\n";
		menu(); // log out of vendor system
	}
	// invalid input
	else {
		traceFile << bank.getTime() << " --- " << (*client).getId() << " entered invalid input.\n";
		cout << "\nInvalid input\n\n";
		purchase(i);
	}
}

// sign in with user id and pin
void Vendor::signIn(){
	string userId, pin;
	Client *client;
	cout << "\nEnter your user ID: ";
	cin >> userId; // user enters userID of client
	int i = bank.clientExists(userId); // checks if the client exists
	// check if the user exists
	if (i >= 0){
		traceFile << bank.getTime() << " --- Unkown user entered " << userId << " as the user ID to sign into\n";
		client = &bank.getClientList()[i];
		// loops until correct pin is entered (user can break out by cancelling)
		while (true){
			cout << "\nEnter your pin or x to cancle: ";
			cin >> pin;
			// if the pin entered matched the correct pin
			if (pin == (*client).getPwd()){
				// the user doesn't have a credit card
				if (!((*client).getChq().getIni())){
					traceFile << "\n" << bank.getTime() << " --- " << userId << " enetered the correct pin but he/she doesn't have a credit card.\n";
					cout << "\nThis user doesn't have a credit card\n";
					menu(); // log out of vendor system
					break;
				}
				// the user has a credit card
				else {
					traceFile << "\n" << bank.getTime() << " --- " << userId << " enetered the correct pin and is now logged in.\n";
					cout << "\nYou are now logged in as " << userId << ".\n\n";
					purchase(i); // set up the purchase
					break;
				}
			}
			// go back to menu if x is entered
			else if (pin == "x"){
				traceFile << bank.getTime() << " --- Unkown user opted to cancel the sign in process.\n";
				cout << endl;
				menu();
			}
			// invalid input (needs to be 4 characters)
			else {
				traceFile << bank.getTime() << " --- Unkown user entered the wrong pin to log into " << userId << "'s account.\n";
				cout << "\nInvalid pin.\n";
			}
		}
	}
	// the user does not exist, can't sign in
	else {
		traceFile << bank.getTime() << " --- Unkown user entered " << userId << " as the user ID to sign into, but that user does not exist\n";
		cout << "\nThe user ID entered does not exist.\n\n";
		menu();
	}
}

// vendor system main menu, can log in or exit
void Vendor::menu(){
	string opt;
	cout << "\nWelcome, enter:\n\n 0 to sign in\n q to quit\n\n ";
	cin >> opt; // chooses to sign in or quit
	if (opt == "0"){
		traceFile << bank.getTime() << " --- Unknown user chose to start the sign in process to the vendor system.\n";
		signIn();
	}
	// exit vendor system
	else if (opt == "q"){
		traceFile << bank.getTime() << " --- Unknown user stopped using the vendor system.\n\n";
	}
	// invalid input
	else {
		traceFile << bank.getTime() << " --- Unknown user entered invalid input in the menu.\n";
		cout << "\nInvalid input\n\n";
		menu();
	}

}