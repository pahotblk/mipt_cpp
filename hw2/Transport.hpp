#pragma once
#include <string>

#include "Inventory.hpp"

class Transport : public InventoryItem {
 public:
  Transport(std::string id, std::string name, int score);

  const std::string& inventoryId() const override { return id_; }
  const std::string& name() const override { return name_; }
  std::string describe() const override;
  int score() const { return score_; }
  virtual bool forNovice() const;

 private:
  std::string id_;
  std::string name_;
  int score_;
};

class Scooter : public Transport, public EnergyConsumer {
 public:
  Scooter(std::string id, std::string name, double energy, int score);
  double dailyEnergy() const override { return energy_; }

 private:
  double energy_;
};

class Bike : public Transport {
 public:
  Bike(std::string id, std::string name, int score);
};

class EBike : public Transport, public EnergyConsumer {
 public:
  EBike(std::string id, std::string name, double energy, int score);
  double dailyEnergy() const override { return energy_; }

 private:
  double energy_;
};

// Электромоноколесо (креативное от меня): новичкам не выдаётся при любой
// простоте.
class Monowheel : public Transport, public EnergyConsumer {
 public:
  Monowheel(std::string id, std::string name, double energy, int score);
  double dailyEnergy() const override { return energy_; }
  bool forNovice() const override { return false; }

 private:
  double energy_;
};