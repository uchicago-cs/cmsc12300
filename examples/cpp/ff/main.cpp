#include"basefrequentflyer.h"
#include"frequentflyer.h"
#include"silverfrequentflyer.h"
#include"goldfrequentflyer.h"
#include<iostream>
using namespace std;

int main()
{
	BaseFrequentFlyer* f[3];
	
	f[0] = new FrequentFlyer ("Cornelius Doe", 23166841, 100);
	f[1] = new SilverFrequentFlyer ("Lucius Doe", 94565432, 100, 5);
	f[2] = new GoldFrequentFlyer("Rufus Doe", 32155994, 100, 100);

	f[0]->addMiles(100);
	f[1]->addMiles(100);
	f[2]->addMiles(100);

	f[0]->printData();
	f[1]->printData();
	f[2]->printData();
	
	delete f[0];
	delete f[1];
	delete f[2];
}
