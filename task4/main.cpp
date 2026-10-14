#include <cstring>
#include <iostream>

struct Change {
  void* where;
  int size;
  char* old_bytes;
};

int main() {
  // Гостиница с отменой действий.
  //
  // Ввод:
  //   B — число корпусов; для каждого корпуса: цена ночи, число этажей F
  //   и F чисел — сколько номеров на каждом этаже (снизу вверх);
  //   Q — число команд, затем Q команд.
  // Команды (корпуса, этажи и номера нумеруются с 1):
  //   checkin b f r — заселить номер r на этаже f корпуса b;
  //   price b x     — установить цену ночи x в корпусе b;
  //   show b        — вывести «price x» и схему корпуса, верхний этаж
  //                   первым: '#' — номер занят, '.' — свободен;
  //   undo          — отменить последнюю команду checkin или price.
  //                   show и команды с ошибкой в историю не попадают.
  // Ошибка (нет такого корпуса, этажа или номера, номер уже занят,
  // отменять нечего) — вывод «error», ничего не меняется.
  //
  // int***: rooms[b][f][r] — 0 свободен, 1 занят. Число этажей и номеров
  // на этаже у корпусов разное и известно только из ввода — это рваный
  // трёхмерный массив в динамической памяти.
  //
  // void*: checkin меняет int, price меняет double. Любое изменение
  // сводится к «записать size байт по адресу target». В историю
  // сохраняются адрес (void* — указатель на данные любого типа), размер и
  // копия старых байт, а undo просто копирует эти байты обратно и не знает,
  // какой тип менялся. Без void* история хранила бы отдельные поля под int
  // и double и вид изменения, а undo разбирал бы каждый вид отдельно.

  int building_count = 0;
  std::cin >> building_count;
  double* prices = new double[building_count];
  int* floor_counts = new int[building_count];
  int** room_counts = new int*[building_count];
  int*** rooms = new int**[building_count];
  for (int b = 0; b < building_count; b++) {
    std::cin >> prices[b] >> floor_counts[b];
    room_counts[b] = new int[floor_counts[b]];
    rooms[b] = new int*[floor_counts[b]];
    for (int f = 0; f < floor_counts[b]; f++) {
      std::cin >> room_counts[b][f];
      rooms[b][f] = new int[room_counts[b][f]]{};
    }
  }

  int command_count = 0;
  std::cin >> command_count;
  Change* history = new Change[command_count];
  int history_size = 0;

  for (int c = 0; c < command_count; c++) {
    char command[8];
    std::cin >> command;

    if (std::strcmp(command, "undo") == 0) {
      if (history_size == 0) {
        std::cout << "error\n";
        continue;
      }
      history_size = history_size - 1;
      Change last = history[history_size];
      std::memcpy(last.where, last.old_bytes, last.size);
      delete[] last.old_bytes;
      continue;
    }

    int b = 0;
    std::cin >> b;
    b--;
    if (b < 0 || b >= building_count) {
      std::cout << "error\n";
      std::cin.ignore(1000, '\n');
      continue;
    }

    if (std::strcmp(command, "show") == 0) {
      std::cout << "price " << prices[b] << '\n';
      for (int f = floor_counts[b] - 1; f >= 0; f--) {
        for (int r = 0; r < room_counts[b][f]; r++) {
          std::cout << (rooms[b][f][r] ? '#' : '.');
        }
        std::cout << '\n';
      }
      continue;
    }

    int occupied = 1;
    double new_price = 0;
    void* target = nullptr;
    void* source = nullptr;
    int size = 0;

    if (std::strcmp(command, "checkin") == 0) {
      int f = 0;
      int r = 0;
      std::cin >> f >> r;
      f--;
      r--;
      if (f < 0 || f >= floor_counts[b] || r < 0 || r >= room_counts[b][f] ||
          rooms[b][f][r] != 0) {
        std::cout << "error\n";
        continue;
      }
      target = &rooms[b][f][r];
      source = &occupied;
      size = sizeof(int);
    } else {
      std::cin >> new_price;
      target = &prices[b];
      source = &new_price;
      size = sizeof(double);
    }

    // общая часть для любого изменения - тип здесь не нужен
    Change change;
    change.where = target;
    change.size = size;
    change.old_bytes = new char[size];
    std::memcpy(change.old_bytes, target, size);
    std::memcpy(target, source, size);
    history[history_size] = change;
    history_size = history_size + 1;
  }

  for (int i = 0; i < history_size; i++) {
    delete[] history[i].old_bytes;
  }
  delete[] history;
  for (int b = 0; b < building_count; b++) {
    for (int f = 0; f < floor_counts[b]; f++) {
      delete[] rooms[b][f];
    }
    delete[] rooms[b];
    delete[] room_counts[b];
  }
  delete[] rooms;
  delete[] room_counts;
  delete[] floor_counts;
  delete[] prices;
  return 0;
}