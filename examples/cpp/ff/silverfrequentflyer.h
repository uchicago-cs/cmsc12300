#ifndef SILVERFREQUENTFLYER_H
#define SILVERFREQUENTFLYER_H

#include "basefrequentflyer.h"

class SilverFrequentFlyer: public BaseFrequentFlyer {
  // Associations
  // Attributes
  public:
    int years;
  // Operations
  public:
  	SilverFrequentFlyer( string name, int number, int miles, int years);
    int realMilesToAirmiles ( int realMiles );
};

#endif
