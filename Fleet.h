#ifndef FLEET_H
#define FLEET_H
#include "CargoShip.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>

//Klasa reprezentuje flotę statków towarowych (Obiekty klasy CargoShip)
class Fleet
{
  //Vector of available vessels
  std::vector<CargoShip> fleet;

public:
  //Add a new vessel to the fleet
  void addVessel(unsigned int carrying_capacity, unsigned int price_per_ton, unsigned int v, unsigned int id);
  //Remove a vessel from the fleet by id
  bool removeVessel(int id);
  //Return number of vessels in the fleet
  size_t getFleetSize() { return fleet.size(); }
  //Return pointers to the begin and end of fleet, you probably shouldn't do this
  std::vector<CargoShip>::iterator getFleetBegin() { return fleet.begin(); }
  std::vector<CargoShip>::iterator getFleetEnd() { return fleet.end(); }

  //Display info about every ship using standard stream
  void displayFleetInfo();
  //Compare functions to use in std::sort
  void sortFleetByPricePerTon()
  {
    std::sort(fleet.begin(), fleet.end(), CargoShip::compareByPricePerTon);
  }

  void sortFleetByID()
  {
    std::sort(fleet.begin(), fleet.end(), CargoShip::compareByID);
  }

};

#endif
