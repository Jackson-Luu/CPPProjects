/*

  == Explanation and rational of testing ==

I have written tests to check that each of the constructors, operators,
and methods visible from the public interface are functioning properly and
as intended. This includes checking values are after function calls are as expected
as well as making sure copy and move calls are appropriately managing both the
original and resulting vectors. Finally, I have also written some tests to
check that the functions are throwing the appropriate exceptions when required.

*/
#include <utility>

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

SCENARIO("Construction of vectors") {
  WHEN("You create two identical default vectors") {
    EuclideanVector a{2};
    EuclideanVector b{2};
    THEN("They should be identical") { REQUIRE(a == b); }
  }
  WHEN("You create two identical vectors with magnitudes") {
    EuclideanVector a{4, 99};
    EuclideanVector b{4, 99};
    THEN("Examine their contents") {
      REQUIRE(a == b);
      REQUIRE(a[0] == 99);
      REQUIRE(b[1] == 99);
      REQUIRE(a[2] == 99);
      REQUIRE(b[3] == 99);
    }
  }
  WHEN("You create a vector with iterators") {
    std::vector<double> vec{5, 20, 66.6};
    EuclideanVector a{vec.begin(), vec.end()};
    THEN("Examine it's contents") {
      REQUIRE(a[0] == vec[0]);
      REQUIRE(a[1] == vec[1]);
      REQUIRE(a[2] == vec[2]);
    }
  }
  WHEN("You create a vector from copy") {
    EuclideanVector a{3};
    a[0] = 7;
    a[1] = 7;
    a[2] = 85.3;
    EuclideanVector b{a};
    THEN("Examine their contents") { REQUIRE(a == b); }
    THEN("Alter the copy") {
      b[0] = 0;
      REQUIRE(a[0] == 7);
    }
  }
  WHEN("You create a vector from move") {
    EuclideanVector a{3};
    a[0] = 7;
    a[1] = 7;
    a[2] = 85.3;
    EuclideanVector b{3};
    b[0] = 7;
    b[1] = 7;
    b[2] = 85.3;
    EuclideanVector c{std::move(a)};
    THEN("Examine their contents") {
      REQUIRE(b == c);
      REQUIRE(a.GetNumDimensions() == 0);
    }
  }
}

SCENARIO("Using operators") {
  WHEN("You call the copy assignment") {
    EuclideanVector a{3};
    a[0] = 11;
    a[1] = 12;
    a[2] = 13;
    EuclideanVector b = a;
    THEN("Examine its contents") { REQUIRE(a == b); }
    THEN("Alter the copy") {
      b[0] = 0;
      REQUIRE(a[0] == 11);
    }
  }
  WHEN("You call the move assignment") {
    EuclideanVector a{3};
    a[0] = 11;
    a[1] = 12;
    a[2] = 13;
    EuclideanVector b{3};
    b[0] = 11;
    b[1] = 12;
    b[2] = 13;
    EuclideanVector c = std::move(a);
    THEN("Examine its contents") {
      REQUIRE(c == b);
      REQUIRE(a.GetNumDimensions() == 0);
    }
  }
  WHEN("You use the subscript operator") {
    EuclideanVector a{3};
    a[0] = 11;
    a[1] = 12;
    a[2] = 13;
    THEN("index into the vector") {
      REQUIRE(a[0] == 11);
      REQUIRE(a[1] == 12);
      REQUIRE(a[2] == 13);
    }
    THEN("set values in the vector") {
      a[0] = 0;
      a[1] = 50.5;
      REQUIRE(a[0] == 0);
      REQUIRE(a[1] == 50.5);
      REQUIRE(a[2] == 13);
    }
  }
  WHEN("You create two vectors") {
    EuclideanVector a{2};
    a[0] = 10;
    a[1] = 24;
    EuclideanVector b{2};
    b[0] = 5;
    b[1] = 3;
    double c = 8;
    THEN("call the addition operator") {
      a += b;
      REQUIRE(a[0] == 15);
      REQUIRE(a[1] == 27);
    }
    THEN("call the subtraction operator") {
      EuclideanVector a{2};
      a[0] = 10;
      a[1] = 24;
      a -= b;
      REQUIRE(a[0] == 5);
      REQUIRE(a[1] == 21);
    }
    THEN("call the multiplication operator") {
      EuclideanVector a{2};
      a[0] = 10;
      a[1] = 24;
      a *= c;
      REQUIRE(a[0] == (8 * 10));
      REQUIRE(a[1] == (8 * 24));
    }
    THEN("call the division operator") {
      EuclideanVector a{2};
      a[0] = 10;
      a[1] = 24;
      a /= c;
      REQUIRE(a[0] == (1.25));
      REQUIRE(a[1] == (3));
    }
  }
  WHEN("You create a vector using different wrappers") {
    EuclideanVector a{3};
    a[0] = 5;
    a[1] = 10;
    a[2] = 15;
    std::vector<double> b{5, 10, 15};
    std::list<double> c{5, 10, 15};
    THEN("Typecast using the operators") {
      auto vec = std::vector<double>{a};
      auto list = std::list<double>{a};
      REQUIRE(vec == b);
      REQUIRE(list == c);
    }
  }
}

SCENARIO("Creation of unit vectors") {
  WHEN("You have two identical vectors") {
    EuclideanVector a{4};
    a[0] = 1;
    a[1] = 2;
    a[2] = 50;
    a[3] = 80.8;
    EuclideanVector b{4};
    b[0] = 1;
    b[1] = 2;
    b[2] = 50;
    b[3] = 80.8;
    THEN("Get their unit vectors") {
      EuclideanVector c{a.CreateUnitVector()};
      EuclideanVector d{b.CreateUnitVector()};
      REQUIRE(c == d);
    }
  }
}

SCENARIO("Calculating Euclidean Norms") {
  WHEN("You have two identical vectors") {
    EuclideanVector a{4};
    a[0] = 1;
    a[1] = 2;
    a[2] = 50;
    a[3] = 80.8;
    EuclideanVector b{4};
    b[0] = 1;
    b[1] = 2;
    b[2] = 50;
    b[3] = 80.8;
    THEN("Get their Euclidean Norms") { REQUIRE(a.GetEuclideanNorm() == b.GetEuclideanNorm()); }
  }
  WHEN("You have an empty vector") {
    EuclideanVector a{0};
    THEN("Get it's Euclidean Norm") {
      REQUIRE_THROWS_WITH(a.GetEuclideanNorm(),
                          "EuclideanVector with no dimensions does not have a norm");
    }
  }
}
SCENARIO("Accessing dimension that doesn't exist") {
  WHEN("You create a vector") {
    EuclideanVector a{2};
    a[0] = 1;
    a[1] = 2;
    THEN("You access a dimension greater doesn't exist") {
      REQUIRE_THROWS_WITH(a.at(2), "Index 2 is not valid for this EuclideanVector object");
      REQUIRE_THROWS_WITH(a.at(-1), "Index -1 is not valid for this EuclideanVector object");
    }
  }
}
