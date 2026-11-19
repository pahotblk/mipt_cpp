#pragma once
#include <iostream>
#include <string>
#include <vector>

template <typename T, int Cap>
class Registry {
 public:
  void add(const T& value) {
    if (size() < Cap) {
      items_.push_back(value);
    }
  }

  int size() const { return static_cast<int>(items_.size()); }

  const T& operator[](int index) const { return items_[index]; }

  void print(std::ostream& out) const {
    for (const T& item : items_) {
      out << item << '\n';
    }
  }

 private:
  std::vector<T> items_;
};

template <typename T, int Cap>
std::ostream& operator<<(std::ostream& out, const Registry<T, Cap>& registry) {
  registry.print(out);
  return out;
}

// Журнал отказов техосмотра.
using RejectedJournal = Registry<std::string, 10>;

// Явная специализация: в журнале отказов записи нумеруются.
template <>
inline void RejectedJournal::print(std::ostream& out) const {
  for (int i = 0; i < size(); ++i) {
    out << i + 1 << ". " << items_[i] << '\n';
  }
}