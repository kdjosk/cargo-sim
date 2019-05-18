#include "Client.h"
#include <iostream>

Client::Client(unsigned int rate,
               unsigned int p_min,
               unsigned int p_max,
               unsigned int w_min,
               unsigned int w_max,
               unsigned int d_min,
               unsigned int d_max,
               unsigned int cargo_max)
  : cargo_appearance_rate(rate), price_minimal(p_min), price_maximal(p_max),
    weight_minimal(w_min), weight_maximal(w_max), duration_minimal(d_min),
    duration_maximal(d_max), max_cargo_amount(cargo_max) {}

bool Client::generateNewCargo()
{
  //First empty the new_cargo std::vector
  new_cargo.clear();

  //Then generate new cargo
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_int_distribution<int> distribution1(0,100);
  std::uniform_int_distribution<int> distribution2(price_minimal, price_maximal);
  std::uniform_int_distribution<int> distribution3(weight_minimal, weight_maximal);
  std::uniform_int_distribution<int> distribution4(duration_minimal, duration_maximal);
  int is_new_cargo, price, weight, duration;

  for(int i = 0; i < max_cargo_amount; ++i)
  {
    is_new_cargo = distribution1(generator);

    if(is_new_cargo <= cargo_appearance_rate)
    {
      price = distribution2(generator);
      weight = distribution3(generator);
      duration = distribution4(generator);
      assert(weight > 0);
      assert(price > 0);
      assert(duration > 0);
      Cargo cargo(weight, price, duration);
      assert(cargo.getWeight() == weight);
      assert(cargo.getMaxPrice() == price);
      assert(cargo.getShippingDuration() == duration);
      new_cargo.push_back(cargo);
    }
  }
}
