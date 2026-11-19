#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Inventory.hpp"
#include "Registry.hpp"
#include "ServiceCenter.hpp"
#include "Things.hpp"
#include "Transport.hpp"

class Fleet {
 public:
  void addTransport(std::unique_ptr<Transport> unit);
  void addThing(std::unique_ptr<Thing> thing);
  void remove(const std::string& id);

  void printList(std::ostream& out) const;
  void printNovice(std::ostream& out) const;
  double totalEnergy() const;

  void setFocus(const std::string& id);
  void printFocus(std::ostream& out) const;

  void printRejected(std::ostream& out) const;  // журнал отказов техосмотра

 private:
  std::vector<std::shared_ptr<InventoryItem>> items_;
  ServiceCenter service_;
  std::weak_ptr<InventoryItem> focus_;
  bool focusWasSet_ = false;
  RejectedJournal rejected_;

  // Позиция с таким id или nullptr
  std::shared_ptr<InventoryItem> find(const std::string& id) const;

  std::vector<std::shared_ptr<InventoryItem>> sorted() const;
};
