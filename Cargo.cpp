#include "Cargo.h"

Cargo::Cargo(unsigned int w, unsigned int mp, unsigned int sd)
  : weight(w), max_price(mp), shipping_duration(sd), days_pending(0)
{
  assert(this->getWeight() == w);
  assert(this->getMaxPrice() == mp);
  assert(this->getShippingDuration() == sd);
  assert(this->getDaysPending() == 0);
}

Cargo::Cargo() : weight(0), max_price(0), shipping_duration(0), days_pending(0)
{
  assert(this->getWeight() == 0);
  assert(this->getMaxPrice() == 0);
  assert(this->getShippingDuration() == 0);
  assert(this->getDaysPending() == 0);
}
