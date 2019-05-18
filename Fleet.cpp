#include "Fleet.h"
#include "CargoShip.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>


void Fleet::addVessel(unsigned int carrying_capacity, unsigned int price_per_ton, unsigned int speed, unsigned int id)
{
  CargoShip vessel(carrying_capacity, price_per_ton, speed, id);
  assert(vessel.getCarryingCapacity() == carrying_capacity);
  assert(vessel.getPricePerTon() == price_per_ton);
  assert(vessel.getSpeed() == speed);
  assert(vessel.getID() == id);
  fleet.push_back(vessel);
}

bool Fleet::removeVessel(int id)
{
  // Iterate through the fleet to find a ship with given id
  // Breaks order because of swapping last ship with the one being deleted
  for(size_t i = 0; i < fleet.size(); ++i)
  {
    if(fleet[i].getID() == id)
    {
      std::swap(fleet[i], fleet[fleet.size() - 1]);
      fleet.pop_back();
      // Return true on succes
      return true;
    }
  }
  // Return false if no ship with given id found
  return false;
}

// Display info about the fleet
void Fleet::displayFleetInfo()
{
  for(size_t i = 0; i < fleet.size(); ++i)
  {
    std::cout << "SHIP ID: " << fleet[i].getID() << " | Max Carrying Capacity: " << fleet[i].getCarryingCapacity()
              << " | Price per ton: " << fleet[i].getPricePerTon()
              << " | Loaded cargo weight: " << fleet[i].getLoadedCargoWeight()
              << " | Speed: " << fleet[i].getSpeed();
    if(fleet[i].getDaysOfJourneyLeft() == 0) std::cout << " | At port" << std::endl;
    else std::cout << " | Days of journey left: " << fleet[i].getDaysOfJourneyLeft() << std::endl;
  }
  std::cout << "==============================================================" << std::endl;
}
