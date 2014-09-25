/*
 * Account.h
 *
 *  Created on: Sep 15, 2014
 *      Author: Team 5
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Account {

	protected:
		float balance;
		bool initialized;
		string type;
		vector<string> transHist;

	public:
		Account();
		Account(float, string);
		~Account();
		float getBal();
		bool getIni();
		void addBal(float);
		string getTime();
		void subBal(float);
		void history();
};

#endif /* ACCOUNT_H_ */
