#include "MainVesselControl.h"
#include <vector>
#include <cmath>
#include <cassert>
#define MINIMAL_LOAD_THRESHOLD 0.95 //percentage of empty space allowed
#define MAXIMAL_JOURNEY_DURATION 30
#define MINIMAL_JOURNEY_DURATION 10

MainVesselControl::MainVesselControl( unsigned int dist ) :
  nextID(0), distance_to_destination(dist) {}

void MainVesselControl::addVessel(Fleet &fleet, unsigned int carrying_capacity,
                                  unsigned int price_per_ton, unsigned int speed)
{
  fleet.addVessel(carrying_capacity, price_per_ton, speed, nextID);
  ++nextID;
}

void MainVesselControl::addFleetFromFile(Fleet &fleet, std::string filename)
{
  std::ifstream file;
  file.open(filename);
  assert(file.good());
  unsigned int carrying_capacity, price_per_ton, speed;

  //Read data from file
  while(file >> carrying_capacity >> price_per_ton >> speed)
  {
    // Add the vessel to the ship
    fleet.addVessel(carrying_capacity, price_per_ton, speed, nextID);
    ++nextID;
  }

  file.close();
}

void MainVesselControl::removeVessel(Fleet &fleet, unsigned int id)
{
  fleet.removeVessel(id);
}

void MainVesselControl::nextDay(Fleet &fleet)
{
  // Iterate through whole fleet
  for(std::vector<CargoShip>::iterator ship = fleet.getFleetBegin(); ship != fleet.getFleetEnd(); ++ship)
  {
    //If the ship is travelling we pass the time
    if(ship->getDaysOfJourneyLeft() > 0)
    {
      unsigned int days = ship->getDaysOfJourneyLeft();
      ship->setDaysOfJourneyLeft(days - 1);
      assert(ship->getDaysOfJourneyLeft() == days - 1);
      if(ship->getDaysOfJourneyLeft() == 0)
      {
         ship->unloadCargo();
         assert(ship->getLoadedCargoWeight() == 0);
      }
    }
    else if((double)ship->getLoadedCargoWeight()/ship->getCarryingCapacity() > MINIMAL_LOAD_THRESHOLD)
    {
      //If the ship is full up to a certain threshold it departs on a journey
        ship->setDaysOfJourneyLeft( ceil( (double) distance_to_destination / ship->getSpeed()) );
        assert(ship->getDaysOfJourneyLeft() == ceil( (double) distance_to_destination / ship->getSpeed()));
    }

  }
}
