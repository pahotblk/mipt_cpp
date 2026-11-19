#pragma once
#include <stdexcept>
#include <string>

// Базовый error, который ловится в main
class FleetError : public std::runtime_error {
 public:
  explicit FleetError(const std::string& message)
      : std::runtime_error(message) {}
};

// Техосмотр отклонил устройство
class InspectionRejected : public FleetError {
 public:
  InspectionRejected() : FleetError("inspection rejected") {}
};

// Некорректное значение при создании
class InvalidArgument : public FleetError {
 public:
  explicit InvalidArgument(const std::string& message) : FleetError(message) {}
};

// Команду не удалось разобрать, нестандартный вид
class CommandError : public FleetError {
 public:
  explicit CommandError(const std::string& message) : FleetError(message) {}
};

// В парке нет позиции с таким id
class NotFound : public FleetError {
 public:
  explicit NotFound(const std::string& id) : FleetError("not found: " + id) {}
};

// попытка создать с уже использованным id
class DuplicateId : public FleetError {
 public:
  explicit DuplicateId(const std::string& id)
      : FleetError("duplicate id: " + id) {}
};