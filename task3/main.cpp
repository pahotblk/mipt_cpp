#include <cstring>
#include <iostream>

const int kRows = 5;
const int kCols = 10;

void Clear(char board[kRows][kCols]) {
  for (int y = 0; y < kRows; y++) {
    for (int x = 0; x < kCols; x++) {
      board[y][x] = ' ';
    }
  }
}

// проверка границ в одном месте, её используют и Put, и Text
bool InBounds(int x, int y) {
  return x >= 0 && x < kCols && y >= 0 && y < kRows;
}

bool Put(char board[kRows][kCols], int x, int y, char c) {
  if (!InBounds(x, y)) {
    return false;
  }
  board[y][x] = c;
  return true;
}

bool Text(char board[kRows][kCols], int x, int y, const char* word) {
  int length = static_cast<int>(std::strlen(word));
  // сначала проверяем, что всё слово влезает, и только потом пишем
  if (length == 0 || !InBounds(x, y) || !InBounds(x + length - 1, y)) {
    return false;
  }
  for (int i = 0; i < length; i++) {
    Put(board, x + i, y, word[i]);
  }
  return true;
}

void Print(const char board[kRows][kCols]) {
  for (int y = 0; y < kRows; y++) {
    for (int x = 0; x < kCols; x++) {
      std::cout << board[y][x];
    }
    std::cout << '\n';
  }
}

void SkipLine() { std::cin.ignore(1000, '\n'); }

int main() {
  char board[kRows][kCols];
  Clear(board);

  char command[100];

  while (std::cin >> command) {
    if (std::strcmp(command, "quit") == 0) {
      break;
    }
    if (std::strcmp(command, "clear") == 0) {
      Clear(board);
    } else if (std::strcmp(command, "print") == 0) {
      Print(board);
    } else if (std::strcmp(command, "put") == 0) {
      int x = 0;
      int y = 0;
      char c = ' ';
      std::cin >> x >> y >> c;
      if (!Put(board, x, y, c)) {
        std::cout << "error\n";
      }
    } else if (std::strcmp(command, "text") == 0) {
      int x = 0;
      int y = 0;
      char word[100];
      std::cin >> x >> y >> word;
      if (!Text(board, x, y, word)) {
        std::cout << "error\n";
      }
    } else {
      std::cout << "error\n";
      SkipLine();
    }
  }
  return 0;
}