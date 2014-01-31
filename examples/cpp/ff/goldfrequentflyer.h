#ifndef GOLDFREQUENTFLYER_H
#define GOLDFREQUENTFLYER_H

#include "basefrequentflyer.h"

class GoldFrequentFlyer: public BaseFrequentFlyer {
  // Associations
  // Attributes
  public:
    int numFlights;
  // Operations
  public:
  	GoldFrequentFlyer ( string name, int number, int miles, int numFlights);
    int realMilesToAirmiles ( int realMiles );
};

#endif
