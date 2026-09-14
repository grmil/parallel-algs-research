#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstddef>

template <typename T = double>
class Array {
    std::vector<T> data;

public:
    Array() = default;
    explicit Array(std::size_t n) : data(n) {}
    Array(std::initializer_list<T> init) : data(init) {}

    std::size_t size() const { return data.size(); }

    // Item access operator definitions
    T& operator[](std::size_t i) { return data[i]; }
    const T& operator[](std::size_t i) const { return data[i]; }

    T& operato
};

template <typename T>
Array<T> operator+(const Array<T>& a, const Array<T>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Array size mismatch");
    }

    Array<T> result(a.size());
    for (std::size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] + b[i];
    }

    return result;
};

template <typename T>
Array<T> operator-(const Array<T>& a, const Array<T>& b) {
  if (a.size() != b.size()) {
    throw std::invalid_argument("Array size mismatch");
  }

  Array<T> result(a.size());
  for (std::size_t i = 0; i < a.size(); ++i) {
    result[i] = a[i] - b[i];
  }

  return result;
}


template <typename T>
Array<T> operator*(const Array<T>& a, const Array<T>& b) {
  if (a.size() != b.size()) {
    throw std::invalid_argument("Array size mismatch");
  }

  Array<T> result(a.size());
  for (std::size_t i = 0; i < a.size(); ++i) {
    result[i] = a[i] * b[i];
  }

  return result;
}

template <typename T>
Array<T> operator/(const Array<T>& a, const Array<T>& b) {
  if (a.size() != b.size()) {
    throw std::invalid_argument("Array size mismatch");
  }

  Array<T> result(a.size());
  for (std::size_t i = 0; i < a.size(); ++i) {
    result[i] = a[i] / b[i];
  }

  return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& v) {
  os << "[";
  for (std::size_t i = 0; i < v.size(); ++i) {
    os << v[i];
    if (i != v.size() - 1) {
      os << ", ";
    }
  }
  os << "]";
  return os;
};
