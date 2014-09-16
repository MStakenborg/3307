/*
 * Account.h
 *
 *  Created on: Sep 15, 2014
 *      Author: Sparky
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>

class Account {

	protected:
		float balance;
		int acctId;
		char acctType[8];
		int pin;

	public:
		Account(float bal, int pinNum, std::string type);
		~Account();
		float getBal();
		void addBal();
		void subBal();
};

#endif /* ACCOUNT_H_ */
