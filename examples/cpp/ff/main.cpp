#include"basefrequentflyer.h"
#include"frequentflyer.h"
#include"silverfrequentflyer.h"
#include"goldfrequentflyer.h"
#include<vector>
#include<memory>
using namespace std;

int main()
{
  vector<unique_ptr<BaseFrequentFlyer>> f;
  f.reserve(3);

  f.emplace_back(unique_ptr<FrequentFlyer>(new FrequentFlyer("Cornelius Doe", 23166841, 100)));
  f.emplace_back(unique_ptr<SilverFrequentFlyer>(new SilverFrequentFlyer("Lucius Doe", 94565432, 100, 5)));
  f.emplace_back(unique_ptr<GoldFrequentFlyer>(new GoldFrequentFlyer("Rufus Doe", 32155994, 100, 100)));

  f[0]->addMiles(100);
  f[1]->addMiles(100);
  f[2]->addMiles(100);

  f[0]->printData();
  f[1]->printData();
  f[2]->printData();
}
