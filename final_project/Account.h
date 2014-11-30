/*
 * Account.h
 *
 *  Created on: Sep 15, 2014
 *      Author: Team 5
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


class Account {

	protected:
		float balance;
		bool initialized;
		std::string type;
		std::vector<std::string> transHist;

	public:
		Account();
		Account(float, std::string);
		~Account();
		float getBal();
		bool getIni();
		void addBal(float);
		void subBal(float);
		void history();
};

#endif /* ACCOUNT_H_ */
