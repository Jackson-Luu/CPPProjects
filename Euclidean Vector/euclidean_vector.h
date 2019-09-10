<<<<<<< HEAD
#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <exception>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // Constructors
  explicit EuclideanVector(int i);
  explicit EuclideanVector(int i, double d);
  explicit EuclideanVector(std::vector<double>::const_iterator begin,
                           std::vector<double>::const_iterator end);
  EuclideanVector(const EuclideanVector& o);
  EuclideanVector(EuclideanVector&& o) noexcept;

  // Destructor
  ~EuclideanVector() = default;

  // Operators
  EuclideanVector& operator=(const EuclideanVector& o);
  EuclideanVector& operator=(EuclideanVector&& o) noexcept;
  double& operator[](int i);
  double operator[](int i) const;
  EuclideanVector& operator+=(const EuclideanVector& o);
  EuclideanVector& operator-=(const EuclideanVector& o);
  EuclideanVector& operator*=(const double d);
  EuclideanVector& operator/=(const double d);
  explicit operator std::vector<double>();
  explicit operator std::list<double>();

  // Methods
  double at(int idx) const;
  double& at(int idx);
  int GetNumDimensions() const;
  double GetEuclideanNorm();
  EuclideanVector CreateUnitVector();
  // Friends
  friend bool operator==(const EuclideanVector& ev1, const EuclideanVector& ev2) {
    bool b = true;
    if (ev1.GetNumDimensions() == ev2.GetNumDimensions()) {
      int len = ev1.GetNumDimensions();
      for (int i = 0; i < len; ++i) {
        if (ev1.at(i) != ev2.at(i)) {
          b = false;
        }
      }
    } else {
      b = false;
    }
    return b;
  }
  friend bool operator!=(const EuclideanVector& ev1, const EuclideanVector& ev2) {
    return !(ev1 == ev2);
  }
  friend EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs) {
    int len = lhs.GetNumDimensions();
    if (len != rhs.GetNumDimensions()) {
      std::string s = "Dimensions of LHS(" + std::to_string(len) + ") and RHS(" +
                      std::to_string(rhs.GetNumDimensions()) + ") do not match";
      throw EuclideanVectorError(s);
    }
    EuclideanVector ev{len};
    for (int i = 0; i < len; ++i) {
      ev[i] = lhs.at(i) + rhs.at(i);
    }
    return ev;
  }
  friend EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs) {
    int len = lhs.GetNumDimensions();
    if (len != rhs.GetNumDimensions()) {
      std::string s = "Dimensions of LHS(" + std::to_string(len) + ") and RHS(" +
                      std::to_string(rhs.GetNumDimensions()) + ") do not match";
      throw EuclideanVectorError(s);
    }
    EuclideanVector ev{len};
    for (int i = 0; i < len; ++i) {
      ev[i] = lhs.at(i) - rhs.at(i);
    }
    return ev;
  }
  friend double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs) {
    int len = lhs.GetNumDimensions();
    if (len != rhs.GetNumDimensions()) {
      std::string s = "Dimensions of LHS(" + std::to_string(len) + ") and RHS(" +
                      std::to_string(rhs.GetNumDimensions()) + ") do not match";
      throw EuclideanVectorError(s);
    }
    double sum = 0;
    for (int i = 0; i < len; ++i) {
      sum += lhs.at(i) * rhs.at(i);
    }
    return sum;
  }
  friend EuclideanVector operator*(const EuclideanVector& lhs, const double rhs) {
    int len = lhs.GetNumDimensions();
    EuclideanVector ev{len};
    for (int i = 0; i < len; ++i) {
      ev[i] = lhs.at(i) * rhs;
    }
    return ev;
  }
  friend EuclideanVector operator*(const double lhs, const EuclideanVector& rhs) {
    int len = rhs.GetNumDimensions();
    EuclideanVector ev{len};
    for (int i = 0; i < len; ++i) {
      ev[i] = rhs.at(i) * lhs;
    }
    return ev;
  }
  friend EuclideanVector operator/(const EuclideanVector& lhs, const double rhs) {
    if (rhs == 0) {
      throw EuclideanVectorError("Invalid vector division by 0");
    }
    int len = lhs.GetNumDimensions();
    EuclideanVector ev{len};
    for (int i = 0; i < len; ++i) {
      ev[i] = lhs.at(i) / rhs;
    }
    return ev;
  }
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) {
    os << "[";
    if (v.GetNumDimensions() > 0) {
      int len = v.GetNumDimensions() - 1;
      int i = 0;
      for (i = 0; i < len; ++i) {
        os << v.at(i) << " ";
      }
      os << v.at(i);
    }
    os << "]";
    return os;
  }

 private:
  std::unique_ptr<double[]> magnitudes_;
  int size_;
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
=======
// TODO(you): Include header guards

#include <exception>
#include <memory>
#include <string>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  explicit EuclideanVector(int i);
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);
  // TODO(you): add more
 private:
  std::unique_ptr<double[]> magnitudes_;
  // TODO(you): add more
};
>>>>>>> fca90ef335fd8446e717ef03c8c63eced725aa2d
