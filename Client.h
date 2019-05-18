#ifndef CLIENT_H
#define CLIENT_H
#include <random>
#include <vector>
#include <cassert>
#include "Cargo.h"

//Klasa reprezentuje klienta, ktory wysyla losowo generowane towary do
//centrum kotroli towarow MainCargoControl
class Client
{
  // Parameters for cargo generation
  unsigned int cargo_appearance_rate; // in %, how likely is a single cargo to be generated
  unsigned int price_minimal;
  unsigned int price_maximal;
  unsigned int weight_minimal;
  unsigned int weight_maximal;
  unsigned int duration_minimal;
  unsigned int duration_maximal;
  unsigned int max_cargo_amount;
  //Newly generated Cargo is stored here
  std::vector<Cargo> new_cargo;

public:
  //Contructors
  Client(unsigned int rate,
         unsigned int p_min,
         unsigned int p_max,
         unsigned int w_min,
         unsigned int w_max,
         unsigned int d_min,
         unsigned int d_max,
         unsigned int cargo_max);
  //Replaces the contents of new_cargo with newly generated cargo
  bool generateNewCargo();
  //returns an iterator pointing at the begining of new_cargo
  std::vector<Cargo>::iterator getCargoBegin(){ return new_cargo.begin(); }
  std::vector<Cargo>::iterator getCargoEnd(){ return new_cargo.end(); }
  //Getters
  unsigned int getCargoAppearanceRate(){ return cargo_appearance_rate; }
  unsigned int getPriceMinimal(){ return price_minimal; }
  unsigned int getPriceMaximal(){ return price_maximal; }
  unsigned int getWeightMinimal(){ return weight_minimal; }
  unsigned int getWeightMaximal(){ return weight_maximal; }
  unsigned int getDurationMinimal(){ return duration_minimal; }
  unsigned int getDurationMaximal(){ return duration_maximal; }
  unsigned int getMaxCargoAmount(){ return max_cargo_amount; }
  unsigned int getNewCargoAmount(){ return new_cargo.size(); }
  //Setters
  void setPriceMinimal(unsigned int p_min){ price_minimal = p_min; }
  void setPriceMaximal(unsigned int p_max){ price_maximal = p_max; }
  void setWeightMinimal(unsigned int w_min){ weight_minimal = w_min; }
  void setWeightMaximal(unsigned int w_max){ weight_maximal = w_max; }
  void setDurationMinimal(unsigned int d_min){ duration_minimal = d_min; }
  void setDurationMaximal(unsigned int d_max){ duration_maximal = d_max; }
  void setMaxCargoAmount(unsigned int cargo_max){ max_cargo_amount = cargo_max; }

};

#endif
