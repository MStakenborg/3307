/*
 * Account.h
 *
 *  Created on: Sep 15, 2014
 *      Author: Team 5
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>

using namespace std;

class Account {

	protected:
		float balance;
		bool initialized;
		string type;

	public:
		Account();
		Account(float, string);
		~Account();
		float getBal();
		bool getIni();
		//void transFunds(Account, int, Account, int);
		void addBal(float);
		int subBal(float);
};

#endif /* ACCOUNT_H_ */
