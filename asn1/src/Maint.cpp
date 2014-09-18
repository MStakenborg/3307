/*
 * Maint.cpp
 *
 *  Created on: Sep 15, 2014
 *      
 */

#include "Maint.h"


int accId;
int trace = 0;  //0 for off 1 for on

/*constructors*/
Maint::Maint(){

}

Maint::Maint(int id) {
	accId = id;
}

int traceState(){
	return trace;
}

Maint::~Maint() {
}

