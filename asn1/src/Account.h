/*
 * Account.h
 *
 *  Created on: Sep 15, 2014
 *      Author: Team 5
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
		Account();
		Account(float, int, std::string, int);
		~Account();
		float getBal();
		int getId();
		int getPin();
		void setId(int);
		void setPin(int);
		//void transFunds(Account, int, Account, int);
		void addBal(float);
		int subBal(float);
};

#endif /* ACCOUNT_H_ */
