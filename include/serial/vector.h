// TODO: Add docs for all of this
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstddef>

template <typename T = double>
class Vector {
    std::vector<T> data;

    void checkSameSize(const Vector<T>& rhs) const {
        if (data.size() != rhs.data.size())
            throw std::invalid_argument("Vector size mismatch");
    }

public:
    Vector() = default;
    explicit Vector(std::size_t n) : data(n) {}
    Vector(std::initializer_list<T> init) : data(init) {}

    // Size, piped from std::vector
    std::size_t size() const { return data.size(); }

    // Item access operator definitions
    T& operator[](std::size_t i) { return data[i]; }
    const T& operator[](std::size_t i) const { return data[i]; }

    // Iterators for loops
    auto begin() { return data.begin(); }
    auto end()   { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end()   const { return data.end(); }

    // Inner Product
    T dot(const Vector<T>& rhs) const {
        checkSameSize(rhs);
        T result{};
        for (std::size_t i = 0; i < size(); ++i) {
            result += data[i] * rhs[i];
        }
        return result;
    }

    // Compound assignment - (vector, vector)
    Vector<T>& operator+=(const Vector<T>& rhs) {
        checkSameSize(rhs);
        for (std::size_t i = 0; i < data.size(); ++i)
            data[i] += rhs.data[i];
        return *this;
    }

    Vector<T>& operator-=(const Vector<T>& rhs) {
        checkSameSize(rhs);
        for (std::size_t i = 0; i < data.size(); ++i)
            data[i] -= rhs.data[i];
        return *this;
    }

    Vector<T>& operator*=(const Vector<T>& rhs) {
        checkSameSize(rhs);
        for (std::size_t i = 0; i < data.size(); ++i)
            data[i] *= rhs.data[i];
        return *this;
    }

    Vector<T>& operator/=(const Vector<T>& rhs) {
        checkSameSize(rhs);
        for (std::size_t i = 0; i < data.size(); ++i)
            data[i] /= rhs.data[i];
        return *this;
    }

    // Compound assignment - vector, scalar
    Vector<T>& operator*=(const T& scalar) {
        for (std::size_t i = 0; i < data.size(); ++i)
            data[i] *= scalar;
        return *this;
    }

    void append(T value) {
      data.push_back(std::move(value));
    }

    T pop() {
      T value = std::move(data.back());
      data.pop_back();
      return value;
    }
};

// (vector, vector)
template <typename T>
Vector<T> operator+(Vector<T> a, const Vector<T>& b) {
    a += b;
    return a;
}

template <typename T>
Vector<T> operator-(Vector<T> a, const Vector<T>& b) {
    a -= b;
    return a;
}

template <typename T>
Vector<T> operator*(Vector<T> a, const Vector<T>& b) {
    a *= b;
    return a;
}

template <typename T>
Vector<T> operator/(Vector<T> a, const Vector<T>& b) {
    a /= b;
    return a;
}

// (vector, scalar) and (scalar, vector)
template <typename T>
Vector<T> operator*(Vector<T> a, const T& scalar) {
    a *= scalar;
    return a;
}

template <typename T>
Vector<T> operator*(const T& scalar, Vector<T> b) {
    b *= scalar;
    return b;
}

// Output stream
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
    os << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
