#ifndef BASEFREQUENTFLYER_H
#define BASEFREQUENTFLYER_H

#include <string>
using namespace std;

class BaseFrequentFlyer {
  // Associations
  // Attributes
  private:
    string name;
    int number;
    int miles;
  // Operations
  public:
  	BaseFrequentFlyer(string name, int number, int miles);  
  	virtual ~BaseFrequentFlyer();
    void addMiles ( int realMiles );
    virtual int realMilesToAirmiles ( int realMiles );
    void printData (  );
};

#endif
