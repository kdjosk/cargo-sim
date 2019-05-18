#ifndef MAINCARGOCONTROL_H
#define MAINCARGOCONTROL_H
#include "Cargo.h"
#include "Client.h"
#include "Fleet.h"
#include "CargoShip.h"
#include <vector>
#include <cassert>
#include <iostream>

//Klasa kontroluje przepływ towarów między klientem a statkami
class MainCargoControl
{
  // Vector of cargo that hasn't yet been distributed
  std::vector<Cargo> pending_cargo;
  // distance to destination
  unsigned int distance_to_destination;
  // total income
  unsigned int total_income;

public:
  //Contructor
  MainCargoControl(unsigned int dist) : distance_to_destination(dist), total_income(0) {};
  unsigned int getTotalIncome(){ return total_income; }
  //Get new cargo from client and add it to the pending_cargo vector
  void getNewCargoFromClient(Client &client);
  //Distribute cargo to the ships
  void distributeCargo(Fleet &fleet);
  //Sort pending cargo by weight in ascending order
  void sortCargoByWeightAsc();
  //End the current day and pass to the next one
  //i.e. use addDayPending() for each cargo left and increase max_price if
  //the cargo is waiting too long
  void nextDay();
  //Display info about the pending cargo
  void displayPendingCargo();
  //Return how many cargo objects are pending
  unsigned int getAmountOfPendingCargo(){ return pending_cargo.size(); }
  unsigned int getDistanceToDestination(){ return distance_to_destination; }
  //iterators
  std::vector<Cargo>::iterator getCargoBegin(){ return pending_cargo.begin(); }
  std::vector<Cargo>::iterator getCargoEnd(){ return pending_cargo.end(); }

};

#endif
