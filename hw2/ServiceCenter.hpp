#pragma once
#include <memory>

#include "Transport.hpp"

class ServiceCenter {
 public:
  std::unique_ptr<Transport> inspect(std::unique_ptr<Transport> unit) const;
};