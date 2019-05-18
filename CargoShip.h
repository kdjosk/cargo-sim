#ifndef CARGOSHIP_H
#define CARGOSHIP_H
#include <string>
#include <iostream>
#include <cassert>
#include "Cargo.h"

//Klasa reprezentuje pojedynczy statek towarowy
class CargoShip
{
  //maximal carrying capacity
  unsigned int carrying_capacity;
  //price per ton of cargo
  unsigned int price_per_ton;
  //Unique ID of the ship
  unsigned int ID;
  //weight of loaded cargo
  unsigned int loaded_cargo_weight;
  //number of days untill the end of the journey,
  //if is equal to 0, then the ship is docked
  unsigned int days_of_journey_left;
  //speed in km / day
  unsigned int speed;

public:
  //Constructors
  CargoShip();
  CargoShip(unsigned int carr_cap, unsigned int prc_per_t, unsigned int v, unsigned int id);
  //Setters
  void setCarryingCapacity(unsigned int cc){ carrying_capacity = cc; }
  void setPricePerTon(unsigned int ppt){ price_per_ton = ppt; }
  void setDaysOfJourneyLeft(unsigned int dojl){ days_of_journey_left = dojl; }
  void setID(int id){ ID = id; }
  void setSpeed(unsigned int v){ speed = v; }
  //add weight of the cargo to loaded_cargo_weight
  bool loadCargo(Cargo cargo);
  //Unload all cargo
  bool unloadCargo();
  //Getters
  unsigned int getCarryingCapacity(){ return carrying_capacity; }
  unsigned int getPricePerTon(){ return price_per_ton; }
  unsigned int getID(){ return ID; }
  unsigned int getSpeed(){ return speed; }
  unsigned int getRemainingLoadCapacity(){ return carrying_capacity - loaded_cargo_weight; }
  unsigned int getLoadedCargoWeight(){ return loaded_cargo_weight; }
  unsigned int getDaysOfJourneyLeft(){ return days_of_journey_left; }

  //Static functions to use for sorting with std::sort
  static bool compareByPricePerTon(CargoShip cs1, CargoShip cs2)
  {
    return cs1.price_per_ton > cs2.price_per_ton;
  }

  static bool compareByID(CargoShip cs1, CargoShip cs2)
  {
    return cs1.ID < cs2.ID;
  }

};

#endif
