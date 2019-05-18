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
#define CARGO_APPEARANCE_RATE 70
#define MIN_CARGO_PRICE 200
#define MAX_CARGO_PRICE 1000
#define MIN_CARGO_WEIGHT 3
#define MAX_CARGO_WEIGHT 20
#define MIN_SHIPPING_DURATION 6
#define MAX_SHIPPING_DURATION 30
#define MAX_CARGO_AMOUNT_PER_DAY 10
#define DISTANCE_TO_DESTINATION 3000 // km

// This version simulates a situation when a fleet is assigned to a specific route

int main()
{
  test_main();
  // Create fleet object
  Fleet main_fleet;
  // Create day counter
  unsigned int day_count = 1;
  // Create MainVesselControl object that assigns ID's and keeps track
  // of current journeys
  MainVesselControl main_vessel_control( DISTANCE_TO_DESTINATION );
  // Create MainCargoControl object that keeps track of all the pending
  // contracts, distributes cargo to ships and interacts with the client
  MainCargoControl main_cargo_control( DISTANCE_TO_DESTINATION );
  // Create a Client object that generates new cargo contracts based on parameters
  // passed through the constructor
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

  // Load fleet from a text file
  main_vessel_control.addFleetFromFile(main_fleet, "fleet.in");
  assert(main_fleet.getFleetSize() > 0);

  char c = '0';
  // Main loop
  while(c != 'x')
  {
    // Display how many days have passed
    std::cout << "DAY " << day_count << std::endl;
    // Acquire new cargo from the client
    main_cargo_control.getNewCargoFromClient(client);
    assert(main_cargo_control.getAmountOfPendingCargo() > 0);
    // Distribute cargo to the ships
    main_cargo_control.distributeCargo(main_fleet);
    // Advance time
    main_cargo_control.nextDay();
    main_vessel_control.nextDay(main_fleet);
    // Sort fleet by id for display purposes
    main_fleet.sortFleetByID();
    // Display total income
    std::cout << "TOTAL INCOME: " << main_cargo_control.getTotalIncome() << std::endl;
    // Display pending cargo contracts
    main_cargo_control.displayPendingCargo();
    // Display info about the state of the fleet
    main_fleet.displayFleetInfo();

    // Increase day counter
    ++day_count;
    // Wait for user input
    while(std::cin >> c){ if(c == 'n') break; }
  }


}










/*
int main()
{
  Client client(80, 123, 445, 1, 15, 10);
  MainCargoControl main_cc;
  Fleet fleet;

  fleet.addVessel(30, 14);
  fleet.addVessel(20, 23);
  //fleet.addVessel(1200, 30);
  //fleet.addVessel(1200, 45);
  //fleet.addVessel(12, 12);

  main_cc.getNewCargoFromClient(client);

  //main_cc.getNewCargoFromClient(client);

  main_cc.sortCargoByWeightAsc();

  main_cc.testPrint();

  main_cc.distributeCargo(fleet);

  for(std::vector<CargoShip>::iterator ship = fleet.getFleetBegin(); ship != fleet.getFleetEnd(); ++ship)
  {
    std::cout << ship->getRemainingLoadCapacity() << " * " ;
  }
  std::cout << std::endl;

  main_cc.sortCargoByWeightAsc();
  main_cc.testPrint();

  main_cc.nextDay();

}*/
