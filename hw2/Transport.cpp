#include "Transport.hpp"

#include <utility>

#include "Errors.hpp"

Transport::Transport(std::string id, std::string name, int score)
    : id_(std::move(id)), name_(std::move(name)), score_(score) {
  if (id_.empty()) {
    throw InvalidArgument("empty id");
  }
  if (score_ < 1 || score_ > 10) {
    throw InvalidArgument("score must be 1..10");
  }
}

std::string Transport::describe() const { return id_ + " " + name_; }

bool Transport::forNovice() const { return score_ >= 6; }

Scooter::Scooter(std::string id, std::string name, double energy, int score)
    : Transport(std::move(id), std::move(name), score), energy_(energy) {
  if (energy_ < 0) {
    throw InvalidArgument("energy must be >= 0");
  }
}

Bike::Bike(std::string id, std::string name, int score)
    : Transport(std::move(id), std::move(name), score) {}

EBike::EBike(std::string id, std::string name, double energy, int score)
    : Transport(std::move(id), std::move(name), score), energy_(energy) {
  if (energy_ < 0) {
    throw InvalidArgument("energy must be >= 0");
  }
}

Monowheel::Monowheel(std::string id, std::string name, double energy, int score)
    : Transport(std::move(id), std::move(name), score), energy_(energy) {
  if (energy_ < 0) {
    throw InvalidArgument("energy must be >= 0");
  }
}