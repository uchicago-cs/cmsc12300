#include "goldfrequentflyer.h"

GoldFrequentFlyer::GoldFrequentFlyer( string name, int number, int miles, int numFlights):
	BaseFrequentFlyer(name,number,miles), numFlights(numFlights)
	{ }

int GoldFrequentFlyer::realMilesToAirmiles ( int realMiles ){
	return realMiles * (1 + numFlights / 10);
}

