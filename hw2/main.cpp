#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Errors.hpp"
#include "Fleet.hpp"
#include "Things.hpp"
#include "Transport.hpp"

void handleAdd(std::istringstream& in, Fleet& fleet) {
  std::string kind, id, name;
  double energy = 0;
  int score = 0;
  in >> kind >> id >> name;

  if (kind == "scooter" || kind == "ebike" || kind == "monowheel") {
    in >> energy >> score;
  } else if (kind == "bike") {
    in >> score;
  } else if (kind == "dock") {
    in >> energy;
  }
  if (!in) {
    throw CommandError("bad arguments");
  }

  if (kind == "scooter") {
    fleet.addTransport(std::make_unique<Scooter>(id, name, energy, score));
  } else if (kind == "ebike") {
    fleet.addTransport(std::make_unique<EBike>(id, name, energy, score));
  } else if (kind == "monowheel") {
    fleet.addTransport(std::make_unique<Monowheel>(id, name, energy, score));
  } else if (kind == "bike") {
    fleet.addTransport(std::make_unique<Bike>(id, name, score));
  } else if (kind == "helmet") {
    fleet.addThing(std::make_unique<Helmet>(id, name));
  } else if (kind == "dock") {
    fleet.addThing(std::make_unique<Dock>(id, name, energy));
  } else if (kind == "lock") {
    fleet.addThing(std::make_unique<Lock>(id, name));
  } else {
    throw CommandError("unknown kind: " + kind);
  }
}

int main() {
  Fleet fleet;
  std::cout << std::fixed << std::setprecision(1);

  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream in(line);
    std::string command;
    if (!(in >> command)) {
      continue;
    }
    if (command == "quit") {
      break;
    }

    try {
      if (command == "add") {
        handleAdd(in, fleet);
      } else if (command == "list") {
        fleet.printList(std::cout);
      } else if (command == "novice") {
        fleet.printNovice(std::cout);
      } else if (command == "energy") {
        std::cout << fleet.totalEnergy() << '\n';
      } else if (command == "show_focus") {
        fleet.printFocus(std::cout);
      } else if (command == "rejected") {
        fleet.printRejected(std::cout);
      } else if (command == "focus" || command == "remove") {
        std::string id;
        if (!(in >> id)) {
          throw CommandError("missing id");
        }
        if (command == "focus") {
          fleet.setFocus(id);
        } else {
          fleet.remove(id);
        }
      } else {
        throw CommandError("unknown command: " + command);
      }
    } catch (const FleetError& e) {
      std::cout << "error: " << e.what() << '\n';
    }
  }
}