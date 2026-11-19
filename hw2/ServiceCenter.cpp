#include "ServiceCenter.hpp"

#include <cctype>
#include <string>

#include "Errors.hpp"

std::unique_ptr<Transport> ServiceCenter::inspect(
    std::unique_ptr<Transport> unit) const {
  std::string lowered = unit->name();
  for (char& c : lowered) {
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  }
  if (lowered.find("broken") != std::string::npos) {
    throw InspectionRejected();
  }
  return unit;
}