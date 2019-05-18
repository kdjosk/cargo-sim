#include "Client.h"
#include "MainCargoControl.h"
#include "MainVesselControl.h"
#include "Fleet.h"
#include "test_main.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <cassert>
#include <string>
#define TEST_FLEET_COUNT 13
#define CARGO_APPEARANCE_RATE 90
#define MIN_CARGO_PRICE 200
#define MAX_CARGO_PRICE 1000
#define MIN_CARGO_WEIGHT 3
#define MAX_CARGO_WEIGHT 20
#define MIN_SHIPPING_DURATION 6
#define MAX_SHIPPING_DURATION 30
#define MAX_CARGO_AMOUNT_PER_DAY 10
#define DISTANCE_TO_DESTINATION 3000 // km

// This version simulates a situation when a fleet is assigned to a specific route

int test_main()
{
  // Only testing interface Classes

  // Create fleet object
  Fleet main_fleet;
  // Create MainVesselControl object that assigns ID's and keeps track
  // of current journeys
  MainVesselControl main_vessel_control( DISTANCE_TO_DESTINATION );
  // Create MainCargoControl object that keeps track of all the pending
  // contracts, distributes cargo to ships and interacts with the client
  MainCargoControl main_cargo_control( DISTANCE_TO_DESTINATION );
  // Create a Client object that generates new cargo contracts based on parameters
  // passed through the constructor
  assert( main_vessel_control.getDistanceToDestination() == DISTANCE_TO_DESTINATION);
  assert( main_cargo_control.getDistanceToDestination() == DISTANCE_TO_DESTINATION);

  Client client(CARGO_APPEARANCE_RATE,
                MIN_CARGO_PRICE,
                MAX_CARGO_PRICE,
                MIN_CARGO_WEIGHT,
                MAX_CARGO_WEIGHT,
                MIN_SHIPPING_DURATION,
                MAX_SHIPPING_DURATION,
                MAX_CARGO_AMOUNT_PER_DAY);

  assert(client.getCargoAppearanceRate() == CARGO_APPEARANCE_RATE);
  assert(client.getPriceMinimal() == MIN_CARGO_PRICE);
  assert(client.getPriceMaximal() == MAX_CARGO_PRICE);
  assert(client.getWeightMinimal() == MIN_CARGO_WEIGHT);
  assert(client.getWeightMaximal() == MAX_CARGO_WEIGHT);
  assert(client.getDurationMinimal() == MIN_SHIPPING_DURATION);
  assert(client.getDurationMaximal() == MAX_SHIPPING_DURATION);
  assert(client.getMaxCargoAmount() == MAX_CARGO_AMOUNT_PER_DAY);

  // TEST MainVesselControl
  assert( main_fleet.getFleetSize() == 0);
  main_vessel_control.addFleetFromFile(main_fleet, "fleet.in");
  assert( main_fleet.getFleetSize() == TEST_FLEET_COUNT);
  // assert statements are implemented inside
  main_vessel_control.nextDay(main_fleet);

  // test adding a vessel
  const int test_carr_cap = 10;
  const int test_price_per_ton = 20;
  const int test_speed = 30;
  main_vessel_control.addVessel(main_fleet, test_carr_cap, test_price_per_ton, test_speed);
  std::vector<CargoShip>::iterator ship = main_fleet.getFleetEnd();
  --ship; // decrement to the last ship in the fleet
  assert(ship->getID() == TEST_FLEET_COUNT); //ids are assigned incrementally
  assert(ship->getCarryingCapacity() == test_carr_cap);
  assert(ship->getPricePerTon() == test_price_per_ton);
  assert(ship->getSpeed() == test_speed);

  //test removing a vessel
  main_vessel_control.removeVessel(main_fleet, TEST_FLEET_COUNT);
  assert(main_fleet.getFleetSize() == TEST_FLEET_COUNT);

  // test MainCargoControl
  // test cargo tranfer from client
  assert(client.getNewCargoAmount() == 0);
  assert(main_cargo_control.getAmountOfPendingCargo() == 0);
  main_cargo_control.getNewCargoFromClient(client);
  assert(client.getNewCargoAmount() > 0);
  assert(client.getNewCargoAmount() == main_cargo_control.getAmountOfPendingCargo());

  //test sorting
  main_cargo_control.sortCargoByWeightAsc();
  Cargo temp;
  for(std::vector<Cargo>::iterator c = main_cargo_control.getCargoBegin() + 1; c != main_cargo_control.getCargoEnd(); ++c)
  {
    //std::cout << c->getWeight() << std::endl;
    assert((c - 1)->getWeight() <= c->getWeight());
  }

  //test cargo distribution, assert statements are implemented inside the function
  main_cargo_control.distributeCargo(main_fleet);

  //test advancing time, assert statements inside
  main_cargo_control.nextDay();

  return 0;


}
