// bar.h
// Header file that creates bars using Bar class w/ its parameters.

#include <iostream>
#include <string>
using namespace std;

//
// Bar
//
class Bar {
 private:
  string name;
  int value;
  string category;

 public:
  // default constructor:
  Bar() {
    name = "";
    value = 0;
    category = "";
  }

  //
  // a second constructor:
  //
  // Parameter passed in constructor Bar object.
  //
  Bar(string name, int value, string category) {
    this->name = name;
    this->value = value;
    this->category = category;
  }

  // destructor: Called automatically by C++ to free the memory associated by the
  // Bar.
  virtual ~Bar() {
    // empty (not needed)
  }

  // getName: returns name
  string getName() {
    return this->name;
  }

  // getValue: returns value
  int getValue() {
    return this->value;
  }

  // getCategory: returns category
  string getCategory() {
    return this->category;
  }

  // operators
  // This allows you to compare two Bar
  // objects.  Comparison should be based on the Bar's value.
  // Less than
  bool operator<(const Bar &other) const {
    if (this->value < other.value) {
      return true;
    }
    return false;
  }
  // Less than or equal to
  bool operator<=(const Bar &other) const {
    if (this->value <= other.value) {
      return true;
    }
    return false;
  }
  // Greater than
  bool operator>(const Bar &other) const {
    if (this->value > other.value) {
      return true;
    }
    return false;
  }
  // Greater than or equal to
  bool operator>=(const Bar &other) const {
    if (this->value >= other.value) {
      return true;
    }
    return false;
  }
};