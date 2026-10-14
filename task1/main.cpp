#include <iomanip>
#include <iostream>

struct MinMax {
  int min;
  int max;
};

// три отдельные функции, массив не меняют - поэтому const
double Average(const int* temps, int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += temps[i];
  }
  return static_cast<double>(sum) / n;
}

MinMax FindMinMax(const int* temps, int n) {
  MinMax result = {temps[0], temps[0]};
  for (int i = 1; i < n; i++) {
    if (temps[i] < result.min) {
      result.min = temps[i];
    }
    if (temps[i] > result.max) {
      result.max = temps[i];
    }
  }
  return result;
}

int CountFrostDays(const int* temps, int n) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (temps[i] < 0) {
      count++;
    }
  }
  return count;
}

int main() {
  int n = 0;
  std::cin >> n;

  int* temps = new int[n];  // массив через new
  for (int i = 0; i < n; i++) {
    std::cin >> temps[i];
  }

  double average = Average(temps, n);
  MinMax range = FindMinMax(temps, n);
  int frost_days = CountFrostDays(temps, n);

  std::cout << std::fixed << std::setprecision(1) << average << '\n';
  std::cout << range.min << ' ' << range.max << '\n';
  std::cout << frost_days << '\n';

  delete[] temps;
  return 0;
}