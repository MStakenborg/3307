/*
* asn1.cpp
*
*  Created on: Sep 15, 2014
*      Author: Team 5
*/

#ifndef BANK_H_
#define BANK_H_

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Client.h"
#include <vector>
#include <iomanip>
#include <fstream>
#include <ctime>

class Bank {

protected:
	float amt;
	std::string userId;
	std::string pin;
	std::string option;
	std::vector<Client> clientList;
	bool trace;
	std::ofstream& traceFile;
	time_t now;
	std::string currentTime;
	std::vector<std::string> creditHistory;

public:
	Bank();
	Bank(std::ofstream&);
	int clientExists(std::string id);
	int openAccount(int i);
	void closeAccount(int i);
	void deposit(int i);
	void withdraw(int i);
	void checkBal(int i);
	void transfer(int i);
	void transferToUser(int i, int user, std::string type);
	int withdrawCheck(int i, std::string type);
	void printInfo(int i);
	void manager();
	void maint();
	void clientOptions(int i);
	void signIn();
	void signUp();
	std::string getTime();
	void menu();
	std::vector<Client>& getClientList();
	void endOfMonth();
	void handlePurchase(int, float, std::string);
	void notifyClient(int i, float);

};
#endif