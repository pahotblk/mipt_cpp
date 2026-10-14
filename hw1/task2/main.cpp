#include <cstring>
#include <iostream>

// все операции - функции одного типа, сумма передаётся по ссылке
using Operation = void (*)(int&);

void PrintError() { std::cout << "error\n"; }

void SkipLine() { std::cin.ignore(1000, '\n'); }

bool ReadAmount(int& amount) {
  std::cin >> amount;
  return amount > 0;
}

void Deposit(int& balance) {
  int amount = 0;
  if (!ReadAmount(amount)) {
    PrintError();
    return;
  }
  balance += amount;
}

void Withdraw(int& balance) {
  int amount = 0;
  if (!ReadAmount(amount) || amount > balance) {
    PrintError();
    return;
  }
  balance -= amount;
}

void Balance(int& balance) { std::cout << balance << '\n'; }

void Reset(int& balance) { balance = 0; }

// своя команда
void Double(int& balance) { balance *= 2; }

// таблица команд: имя + указатель на функцию
struct Command {
  const char* name;
  Operation action;
};

const Command kCommands[] = {
    {"deposit", Deposit}, {"withdraw", Withdraw}, {"balance", Balance},
    {"reset", Reset},     {"double", Double},
};
const int kCommandCount = sizeof(kCommands) / sizeof(kCommands[0]);

Operation FindCommand(const char* name) {
  for (int i = 0; i < kCommandCount; i++) {
    if (std::strcmp(kCommands[i].name, name) == 0) {
      return kCommands[i].action;
    }
  }
  return nullptr;
}

int main() {
  int balance = 0;
  char name[100];

  while (std::cin >> name) {
    if (std::strcmp(name, "stop") == 0) {
      break;
    }
    Operation action = FindCommand(name);
    if (action == nullptr) {
      PrintError();
      SkipLine();
      continue;
    }
    action(balance);  // вызов по указателю, без цепочки if
  }
  return 0;
}