#include "assignments/ev/euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm
#include <cassert>
#include <iterator>
#include <math.h>
#include <utility>

// Standard constructor
EuclideanVector::EuclideanVector(int i, double d) : magnitudes_{std::make_unique<double[]>(i)} {
  for (auto idx = 0; idx < i; ++idx) {
    magnitudes_[idx] = d;
  }
  size_ = i;
}

// Default constructor - delegated
EuclideanVector::EuclideanVector(int i) : EuclideanVector(i, 0.0) {}

// Iterator constructor
EuclideanVector::EuclideanVector(std::vector<double>::const_iterator begin,
                                 std::vector<double>::const_iterator end)
  : magnitudes_{std::make_unique<double[]>(std::distance(begin, end))} {
  int i = 0;
  for (auto it = begin; it != end; ++it) {
    magnitudes_[i] = *it;
    i++;
  }
  size_ = i;
}

// Copy constructor
EuclideanVector::EuclideanVector(const EuclideanVector& o)
  : magnitudes_{std::make_unique<double[]>(o.size_)}, size_{o.size_} {
  for (int i = 0; i < o.size_; ++i) {
    magnitudes_[i] = o.magnitudes_.get()[i];
  }
}

// Move constructor
EuclideanVector::EuclideanVector(EuclideanVector&& o) noexcept
  : magnitudes_{std::move(o.magnitudes_)}, size_{o.size_} {
  o.size_ = 0;
}

// Copy assignment
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& o) {
  for (int i = 0; i < o.size_; ++i) {
    magnitudes_[i] = o.magnitudes_.get()[i];
  }
  size_ = o.size_;
  return *this;
}
// Move assignment
EuclideanVector& EuclideanVector::operator=(EuclideanVector&& o) noexcept {
  magnitudes_ = std::move(o.magnitudes_);
  size_ = o.size_;
  o.size_ = 0;
  return *this;
}

// Subscript operators
double& EuclideanVector::operator[](int i) {
  assert(i < size_);
  return magnitudes_.get()[i];
}

double EuclideanVector::operator[](int i) const {
  assert(i < size_);
  return magnitudes_.get()[i];
}

// Compound operators
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& o) {
  if (o.GetNumDimensions() != size_) {
    std::string s = "Dimensions of LHS(" + std::to_string(size_) + ") and RHS(" +
                    std::to_string(o.GetNumDimensions()) + ") do not match";
    throw EuclideanVectorError(s);
  }
  for (int i = 0; i < size_; ++i) {
    magnitudes_[i] += o.magnitudes_.get()[i];
  }
  return *this;
}

EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& o) {
  if (o.GetNumDimensions() != size_) {
    std::string s = "Dimensions of LHS(" + std::to_string(size_) + ") and RHS(" +
                    std::to_string(o.GetNumDimensions()) + ") do not match";
    throw EuclideanVectorError(s);
  }
  for (int i = 0; i < size_; ++i) {
    magnitudes_[i] -= o.magnitudes_.get()[i];
  }
  return *this;
}

EuclideanVector& EuclideanVector::operator*=(const double d) {
  for (int i = 0; i < size_; ++i) {
    magnitudes_[i] *= d;
  }
  return *this;
}

EuclideanVector& EuclideanVector::operator/=(const double d) {
  if (d == 0) {
    throw EuclideanVectorError("Invalid vector division by 0");
  }
  for (int i = 0; i < size_; ++i) {
    magnitudes_[i] /= d;
  }
  return *this;
}

// Type Conversion operators
EuclideanVector::operator std::vector<double>() {
  std::vector<double> vec;
  for (int i = 0; i < size_; ++i) {
    vec.push_back(magnitudes_[i]);
  }
  return vec;
}
EuclideanVector::operator std::list<double>() {
  std::list<double> li;
  for (int i = 0; i < size_; ++i) {
    li.push_back(magnitudes_[i]);
  }
  return li;
}

// Methods
double EuclideanVector::at(int idx) const {
  if (idx < 0 || idx >= size_) {
    std::string s =
        "Index " + std::to_string(idx) + " is not valid for this EuclideanVector object";
    throw EuclideanVectorError(s);
  }
  return magnitudes_[idx];
}

double& EuclideanVector::at(int idx) {
  if (idx < 0 || idx >= size_) {
    std::string s =
        "Index " + std::to_string(idx) + " is not valid for this EuclideanVector object";
    throw EuclideanVectorError(s);
  }
  return magnitudes_[idx];
}

int EuclideanVector::GetNumDimensions() const {
  return size_;
}
double EuclideanVector::GetEuclideanNorm() {
  if (size_ == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a norm");
  }
  double sum = 0;
  for (int i = 0; i < size_; ++i) {
    sum += pow(magnitudes_[i], 2);
  }
  return sqrt(sum);
}

EuclideanVector EuclideanVector::CreateUnitVector() {
  if (size_ == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a unit vector");
  }
  double norm = this->GetEuclideanNorm();
  if (norm == 0) {
    throw EuclideanVectorError(
        "EuclideanVector with euclidean normal of 0 does not have a unit vector");
  }
  EuclideanVector ev = EuclideanVector{size_};
  for (int i = 0; i < size_; ++i) {
    ev[i] = magnitudes_[i] / norm;
  }
  return ev;
}
