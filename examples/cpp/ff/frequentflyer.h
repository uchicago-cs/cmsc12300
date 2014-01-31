#ifndef FREQUENTFLYER_H
#define FREQUENTFLYER_H

#include "basefrequentflyer.h"

class FrequentFlyer: public BaseFrequentFlyer {
  // Associations
  // Attributes
  // Operations
  public:
	FrequentFlyer(string name, int number, int miles);
    int realMilesToAirmiles ( int realMiles );
};

#endif
