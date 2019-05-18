#ifndef MAIN_VESSEL_CONTROL
#define MAIN_VESSEL_CONTROL
#include "Fleet.h"
#include "CargoShip.h"
#include "MainCargoControl.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

class MainVesselControl
{
  // keeps track of assigning id's
  unsigned int nextID;
  // distance to destination
  unsigned int distance_to_destination;

public:
  MainVesselControl( unsigned int dist);
  //Departs full or almost full vessels and docks the ones which have finished
  //their journey
  void nextDay( Fleet &fleet);
  // Add vessel to the given fleet
  void addVessel( Fleet &fleet, unsigned int carrying_capacity, unsigned int price_per_ton, unsigned int speed);
  // Add many ships to a given fleet
  void addFleetFromFile( Fleet &fleet, std::string filename);
  // Remove a vessel from a given fleet
  void removeVessel( Fleet &fleet, unsigned int id);
  unsigned int getDistanceToDestination() { return distance_to_destination; }
};






#endif
