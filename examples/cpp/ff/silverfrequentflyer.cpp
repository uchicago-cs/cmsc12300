#include "silverfrequentflyer.h"

SilverFrequentFlyer::SilverFrequentFlyer( string name, int number, int miles, int years):
	BaseFrequentFlyer(name, number, miles), years(years)
{}
	
	

int SilverFrequentFlyer::realMilesToAirmiles ( int realMiles ){
	return realMiles * (1 + years);
}

