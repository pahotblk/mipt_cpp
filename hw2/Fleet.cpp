#include "Fleet.hpp"

#include <algorithm>
#include <utility>

#include "Errors.hpp"

void Fleet::addTransport(std::unique_ptr<Transport> unit) {
  if (find(unit->inventoryId()) != nullptr) {
    throw DuplicateId(unit->inventoryId());
  }
  std::string entry = unit->describe();
  std::unique_ptr<Transport> accepted;
  try {
    accepted = service_.inspect(std::move(unit));
  } catch (const InspectionRejected&) {
    rejected_.add(entry);
    throw;
  }
  items_.push_back(std::move(accepted));
}

void Fleet::addThing(std::unique_ptr<Thing> thing) {
  if (find(thing->inventoryId()) != nullptr) {
    throw DuplicateId(thing->inventoryId());
  }
  items_.push_back(std::move(thing));
}

void Fleet::remove(const std::string& id) {
  auto it = std::find_if(items_.begin(), items_.end(), [&id](const auto& item) {
    return item->inventoryId() == id;
  });
  if (it == items_.end()) {
    throw NotFound(id);
  }
  items_.erase(it);
}

void Fleet::printList(std::ostream& out) const {
  for (const auto& item : sorted()) {
    out << *item << '\n';
  }
}

void Fleet::printNovice(std::ostream& out) const {
  for (const auto& item : sorted()) {
    const auto* transport = dynamic_cast<const Transport*>(item.get());
    if (transport != nullptr && transport->forNovice()) {
      out << *item << '\n';
    }
  }
}

double Fleet::totalEnergy() const {
  double total = 0;
  for (const auto& item : items_) {
    const auto* consumer = dynamic_cast<const EnergyConsumer*>(item.get());
    if (consumer != nullptr) {
      total += consumer->dailyEnergy();
    }
  }
  return total;
}

void Fleet::setFocus(const std::string& id) {
  std::shared_ptr<InventoryItem> item = find(id);
  if (item == nullptr) {
    throw NotFound(id);
  }
  focus_ = item;
  focusWasSet_ = true;
}

void Fleet::printFocus(std::ostream& out) const {
  if (!focusWasSet_) {
    out << "no focus\n";
    return;
  }
  if (std::shared_ptr<InventoryItem> item = focus_.lock()) {
    out << *item << '\n';
  } else {
    out << "removed\n";
  }
}

void Fleet::printRejected(std::ostream& out) const { out << rejected_; }

std::shared_ptr<InventoryItem> Fleet::find(const std::string& id) const {
  for (const auto& item : items_) {
    if (item->inventoryId() == id) {
      return item;
    }
  }
  return nullptr;
}

std::vector<std::shared_ptr<InventoryItem>> Fleet::sorted() const {
  std::vector<std::shared_ptr<InventoryItem>> copy = items_;
  std::sort(copy.begin(), copy.end(),
            [](const auto& a, const auto& b) { return *a < *b; });
  return copy;
}
