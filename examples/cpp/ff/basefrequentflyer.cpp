#include "basefrequentflyer.h"
#include <iostream>
#include <iomanip>
using namespace std;

BaseFrequentFlyer::~BaseFrequentFlyer()
	{ }
	
BaseFrequentFlyer::BaseFrequentFlyer ( string name, int number, int miles ):
  name(name), number(number), miles(miles) 
  {  }  

void BaseFrequentFlyer::addMiles ( int realMiles ){
	miles += realMilesToAirmiles( realMiles );
}

int BaseFrequentFlyer::realMilesToAirmiles ( int realMiles ){
	return realMiles;
}

void BaseFrequentFlyer::printData (  ){
	cout << setw(20) << name << setw(10) << "#" << number << setw(10) << miles << "mi" << endl;
}

