#include "MainCargoControl.h"
#include "Fleet.h"
#include "Client.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <assert.h>
#define DAYS_PER_MAX_PRICE_INCREASE 3
#define PRICE_INCREASE_COEFICIENT 1.15

void MainCargoControl::getNewCargoFromClient(Client &client)
{
  //Create new random cargo objects
  client.generateNewCargo();
  //Copy new cargo objects from client to pending_cargo
  for(std::vector<Cargo>::iterator it = client.getCargoBegin(); it != client.getCargoEnd(); ++it)
  {
    pending_cargo.push_back(*it);
  }
}

// Sort cargo by weight in ascending order
void MainCargoControl::sortCargoByWeightAsc()
{
  std::sort(pending_cargo.begin(), pending_cargo.end(), Cargo::compareByWeight);
}

// Advance time for cargo
void MainCargoControl::nextDay()
{
  for(int i = 0; i < pending_cargo.size(); ++i)
  {
    pending_cargo[i].addDayPending();
    //Increase price if the cargo is pending for long enough
    if(pending_cargo[i].getDaysPending() > 0 && pending_cargo[i].getDaysPending() % DAYS_PER_MAX_PRICE_INCREASE)
    {
      unsigned int max_price = pending_cargo[i].getMaxPrice();
      pending_cargo[i].setMaxPrice(max_price * PRICE_INCREASE_COEFICIENT );
      assert(pending_cargo[i].getMaxPrice() == (int) max_price * PRICE_INCREASE_COEFICIENT );
    }
  }


}

// Distribute pending cargo to ships
void MainCargoControl::distributeCargo(Fleet &fleet)
{
  // Sort fleet by price so the algorithm starts with the most expensive ships
  // for maximum profit
  fleet.sortFleetByPricePerTon();
  //iterate through all ships
  for(std::vector<CargoShip>::iterator ship = fleet.getFleetBegin(); ship != fleet.getFleetEnd(); ++ship)
  {
    // if the ship is travelling then cannot load cargo on it
    if(ship->getDaysOfJourneyLeft()) continue;
    // sort cargo so the algorithm starts with the lightest one
    this->sortCargoByWeightAsc();
    unsigned int max_carrying_capacity = ship->getRemainingLoadCapacity(),
                 journey_duration = ceil( (double) distance_to_destination / ship->getSpeed() );

    assert(max_carrying_capacity > 0);
    assert(journey_duration > 0);

    // two dimensional dp array, dp[i][j] is the maximal weight that can be
    // assigned to the ship with capacity of j using the first i elements of cargo
    // is_added[i][j] means that the i-th cargo has been considered as loaded
    // if the ships carrying capacity would be j
    std::vector< std::vector<unsigned int> > dp(pending_cargo.size() + 1, std::vector<unsigned int>(max_carrying_capacity + 1, 0));
    std::vector< std::vector<bool> > is_added(pending_cargo.size() + 1, std::vector<bool>(max_carrying_capacity + 1, 0));
    assert(dp.size() == pending_cargo.size() + 1 && dp[0].size() == max_carrying_capacity + 1);
    assert(is_added.size() == pending_cargo.size() + 1 && is_added[0].size() == max_carrying_capacity + 1);

    //Approximate multiknapsack algorithm - first assign cargo to the ship with the highest
    //price per ton by using the single knapsack algorithm, move to the next ship and repeat
    unsigned int cost;
    for(int i = 1; i < pending_cargo.size() + 1; ++i)
    {
      //cost to see if the client can afford to load the cargo
      cost = ship->getPricePerTon()*pending_cargo[i - 1].getWeight();
      assert(cost > 0);

      /* Main loop of the algorithm */
      for(int j = 1; j < max_carrying_capacity + 1; ++j)
      {
        if(pending_cargo[i - 1].getWeight() > j || cost > pending_cargo[i - 1].getMaxPrice()
           || journey_duration > pending_cargo[i - 1].getShippingDuration())
        {
          // Cannot add this cargo so previous optimal solution for capacity j
          // still holds
          dp[i][j] = dp[i - 1][j];
        }
        else
        {
          //if it can be improved then add the cargo
          if(dp[i - 1][j] < dp[i - 1][j - pending_cargo[i - 1].getWeight()] + pending_cargo[i - 1].getWeight())
          {
            dp[i][j] = dp[i - 1][j - pending_cargo[i - 1].getWeight()] + pending_cargo[i - 1].getWeight();
            is_added[i][j] = true;
          }
          else
          {
            // If the optimal solution for capacity j cannot be improved upon
            // by adding i-th cargo then we omit the i-th cargo
            dp[i][j] = dp[i - 1][j];
          }
        }
      }
    }

    //Check which Cargo could've been loaded and load it to the ship, also remove
    //from the record of pending cargo
    for(int i = pending_cargo.size(); i > 0;)
    {
      for(int j = max_carrying_capacity; j > 0;)
      {
        assert(i > 0);
        assert(j > 0);
        if(is_added[i][j]) //check if the i-th cargo was added
        {
          unsigned int weight = pending_cargo[i - 1].getWeight();
          //Move the iterator to the cargo that was added
          j -= weight;
          assert(j >= 0);
          // Load the cargo
          ship->loadCargo(pending_cargo[i - 1]);
          // Add profit to income
          total_income += ship->getPricePerTon() * weight;
          //swap with the last and delete the last element
          std::swap(pending_cargo[i - 1], pending_cargo[pending_cargo.size() - 1]);
          pending_cargo.pop_back();
          --i;
        }
        else  --i;
        if(i < 1) break;
      }
    }
  }

}

// Display info about pending cargo
void MainCargoControl::displayPendingCargo()
{
  std::cout << "===pending_cargo====" << std::endl;
  for(int i = 0; i < pending_cargo.size(); ++i)
  {
    std::cout << "Weight: " << pending_cargo[i].getWeight() << " | "
              << "Max Price: " << pending_cargo[i].getMaxPrice() << " | "
              << "Days pending: " << pending_cargo[i].getDaysPending() << std::endl;
  }
  std::cout << "====================" << std::endl;
}
