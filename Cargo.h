#ifndef CARGO_H
#define CARGO_H
#include <cassert>

// Klasa reprezentuje pojedynczy towar o danej wadze i maksymalnej cenie
class Cargo
{
  // weight of the cargo
  unsigned int weight;
  // maximum price that is going to be paid for this cargo
  unsigned int max_price;
  // for how many days the cargo has been pending
  unsigned int days_pending;
  // how many days the journey can take
  unsigned int shipping_duration;

public:
  // w - weight, mp - max price, sd - shipping duration
  Cargo(unsigned int w, unsigned int mp, unsigned int sd);
  // Default constructor
  Cargo();

  void setWeight(unsigned int w){ weight = w; }
  void setMaxPrice(unsigned int mp){ max_price = mp; }
  void setShippingDuration(unsigned int sd){ shipping_duration = sd; }
  // Use to advance time
  void addDayPending(){ ++days_pending; }

  unsigned int getWeight(){ return weight; }
  unsigned int getMaxPrice(){ return max_price; }
  unsigned int getDaysPending(){ return days_pending; }
  unsigned int getShippingDuration(){ return shipping_duration; }

  //return true if c2 is heavier than c1, can be used for std::sort
  static bool compareByWeight(Cargo c1, Cargo c2){ return c1.weight < c2.weight; }

};

#endif
