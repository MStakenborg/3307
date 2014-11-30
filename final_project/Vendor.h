/*
* vendor.h
*
*  Created on: Nov 29, 2014
*      Author: Team 14
*/

#ifndef VENDOR_H_
#define VENDOR_H_

#include "Bank.h"

class Vendor {

protected:
	std::ofstream& traceFile;
	Bank& bank;
	std::vector<std::string> purchHistory;

public:
	Vendor(std::ofstream&, Bank&);
	void menu();
	void signIn();
	void purchase(int);
	void randomInit();
	void handlePurchase(int, float, std::string);
};
#endif