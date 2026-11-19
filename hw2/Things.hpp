#pragma once
#include <string>

#include "Inventory.hpp"

class Thing : public InventoryItem {
 public:
  Thing(std::string id, std::string name);

  const std::string& inventoryId() const override { return id_; }
  const std::string& name() const override { return name_; }
  std::string describe() const override;

 private:
  std::string id_;
  std::string name_;
};

class Helmet : public Thing {
 public:
  Helmet(std::string id, std::string name);
};

class Dock : public Thing, public EnergyConsumer {
 public:
  Dock(std::string id, std::string name, double energy);
  double dailyEnergy() const override { return energy_; }

 private:
  double energy_;
};

// Противоугонный замок.
class Lock : public Thing {
 public:
  Lock(std::string id, std::string name);
};