#pragma once
#include <iostream>
#include <string>

class InventoryItem {
 public:
  virtual const std::string& inventoryId() const = 0;
  virtual const std::string& name() const = 0;
  virtual std::string describe() const = 0;

  virtual ~InventoryItem() = default;
};

class EnergyConsumer {
 public:
  virtual double dailyEnergy() const = 0;

  virtual ~EnergyConsumer() = default;
};

std::ostream& operator<<(std::ostream& out, const InventoryItem& item);

bool operator<(const InventoryItem& a, const InventoryItem& b);

bool operator==(const InventoryItem& a, const InventoryItem& b);