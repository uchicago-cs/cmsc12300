#include "frequentflyer.h"

FrequentFlyer::FrequentFlyer(string name, int number, int miles): 
	BaseFrequentFlyer(name, number, miles)
	{ }

int FrequentFlyer::realMilesToAirmiles ( int realMiles ){
	return realMiles;
}

