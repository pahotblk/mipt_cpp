#include "Things.hpp"

#include <utility>

#include "Errors.hpp"

Thing::Thing(std::string id, std::string name)
    : id_(std::move(id)), name_(std::move(name)) {
  if (id_.empty()) {
    throw InvalidArgument("empty id");
  }
}

std::string Thing::describe() const { return id_ + " " + name_; }

Helmet::Helmet(std::string id, std::string name)
    : Thing(std::move(id), std::move(name)) {}

Dock::Dock(std::string id, std::string name, double energy)
    : Thing(std::move(id), std::move(name)), energy_(energy) {
  if (energy_ < 0) {
    throw InvalidArgument("energy must be >= 0");
  }
}

Lock::Lock(std::string id, std::string name)
    : Thing(std::move(id), std::move(name)) {}