#include "CargoShip.h"
#include <cassert>

CargoShip::CargoShip(unsigned int carr_cap, unsigned int prc_per_t, unsigned int v, unsigned int id)
  : carrying_capacity(carr_cap), price_per_ton(prc_per_t), speed(v), ID(id), days_of_journey_left(0), loaded_cargo_weight(0)
{
  assert(this->getCarryingCapacity() == carr_cap);
  assert(this->getPricePerTon() == prc_per_t);
  assert(this->getID() == id);
  assert(this->getDaysOfJourneyLeft() == 0);
  assert(this->getLoadedCargoWeight() == 0);
  assert(this->getSpeed() == v);
}

CargoShip::CargoShip()
  : carrying_capacity(0), price_per_ton(0), speed(0), ID(0), days_of_journey_left(0), loaded_cargo_weight(0)
{
  assert(this->getCarryingCapacity() == 0);
  assert(this->getPricePerTon() == 0);
  assert(this->getSpeed() == 0);
  assert(this->getID() == 0);
  assert(this->getDaysOfJourneyLeft() == 0);
  assert(this->getLoadedCargoWeight() == 0);
}

bool CargoShip::unloadCargo()
{
  // ALL cargo is being unloaded
  loaded_cargo_weight = 0;
  assert(this->getLoadedCargoWeight() == 0);
}

bool CargoShip::loadCargo(Cargo cargo)
{
  // Only load the cargo if the ship is at port and if it fits
  if(days_of_journey_left == 0 && loaded_cargo_weight + cargo.getWeight() <= carrying_capacity)
  {
    // Add weight of the cargo to total weight of loaded cargo on the ship
    loaded_cargo_weight += cargo.getWeight();
    // Return true on success
    return true;
  }
  // return false if cannot load the cargo
  else return false;
}
