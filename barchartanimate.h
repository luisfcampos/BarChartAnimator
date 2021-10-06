// barchartanimate.h
// Header file used to animate barcharts from barchart.h using BarChartAnimate
// class.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <unistd.h>
#include "barchart.h"

using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
 private:
  //
  // Private member variables for the abstraction.
  // This implementation uses a low-level C array, bars, to store a list of
  // BarCharts.  As a result, you must also keep track of the number of
  // elements stored (size) and the capacity of the array (capacity).
  // This IS dynamic array, so it must expand automatically, as needed.
  //
  BarChart* barcharts;  // pointer to a C-style array
  int size;
  int capacity;
  map<string, string> colorMap;
  string title;
  string xlabel;
  string source;

 public:
  // a parameterized constructor:
  // Like the ourvector, the barcharts C-array should be constructed here
  // with a capacity of 4.
  BarChartAnimate(string title, string xlabel, string source) {
    // TO DO:  Write this constructor.
    barcharts = new BarChart[4];
    size = 0;
    capacity = 4;

    this->title = title;
    this->xlabel = xlabel;
    this->source = source;

    colorMap["East Asia"] = COLORS.at(0);
    colorMap["Middle East"] = COLORS.at(1);
    colorMap["South Asia"] = COLORS.at(2);
    colorMap["Europe"] = COLORS.at(3);
    colorMap["North America"] = COLORS.at(4);
    colorMap["Latin America"] = COLORS.at(5);
  }

  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated
  // by BarChartAnimate.
  //
  virtual ~BarChartAnimate() {
    if (barcharts != nullptr) {
      delete[] barcharts;
    }
  }

  
  // addFrame:
  // adds a new BarChart to the BarChartAnimate object from the file stream.
  // if the barcharts has run out of space, double the capacity (see
  // ourvector.h for how to double the capacity).
  // See application.cpp and handout for pre and post conditions.
  void addFrame(ifstream& file) {
    if (size == capacity) {  // checks if out of space
      int newCapacity = capacity * 2;
      BarChart* newbarcharts = new BarChart[newCapacity];
      for (int i = 0; i < size; i++) {
        newbarcharts[i] = barcharts[i];
      }
      delete[] barcharts;
      barcharts = newbarcharts;
      capacity = newCapacity;
    }
    int numGroup = 0;
    string numGroupStr = "";
    getline(file, numGroupStr, '\n');
    getline(file, numGroupStr, '\n');

    if (numGroupStr != "") {  // checks if blank line
      numGroup = stoi(numGroupStr);
      string year = "";
      string name = "";
      string country = "";
      string valueStr= "";
      string category = "";
      int value = 0;
      BarChart newbc(numGroup);

      for (int i = 0; i < numGroup; i++) {  // iterates through group
        getline(file, year, ',');
        getline(file, name, ',');
        getline(file, country, ',');
        getline(file, valueStr, ',');
        value = stoi(valueStr);
        getline(file, category, '\n');
        int colorCount = 0;

        if (colorMap.count(category)) {  // check if color map key exists
          auto it = find(COLORS.begin(), COLORS.end(), colorMap[category]);
          if (it != COLORS.end()) {
            colorCount = it - COLORS.begin();
          }
        } else if (!colorMap.count(category)) {
            colorMap[category] = COLORS.at(colorCount);  // sets key to curr
            colorCount++;  // increments curr
            if (colorCount > 6) {  // checks if reached end of COLORS vector
              colorCount = 0;
            }
        }
        Bar newBar(name, value, category);  // makes new Bar
        newbc.addBar(newBar.getName(), newBar.getValue(), newBar.getCategory());
          // adds new Bar to bar chart
      }
      newbc.setFrame(year);  // adds frame to barchart
      barcharts[this->size] = newbc;  // adds barchart to end of barcharts
      this->size++;  // increments curr size
    }
  }

  // animate:
  // this function plays each frame stored in barcharts.  In order to see the
  // animation in the terminal, you must pause between each frame.  To do so,
  // type:  usleep(3 * microsecond);
  // Additionally, in order for each frame to print in the same spot in the
  // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
  // in between each frame.
  void animate(ostream& output, int top, int endIter) {
    unsigned int microsecond = 50000;

    if (endIter == -1) {  // check if endIter = -1
      endIter = this->size;  // sets to entire size of barcharts
    }

    for (int i = 0; i <= endIter; i++) {  // loop through barcharts
      usleep(3 * microsecond);
      output << CLEARCONSOLE;

      output << WHITE;
      output << this->title << endl;
      output << WHITE;
      output << this->source << endl;
      
      barcharts[i].graph(cout, colorMap, top);
      output << WHITE;
      output << this->xlabel << endl;
      output << "Frame: " << barcharts[i].getFrame() << endl;
    }
  }
  
  // animate w/ playback speed:
  // this function plays each frame stored in barcharts with an addition of a
  // playback speed.
  // In order to see the animation in the terminal, you must pause between
  // each frame.  To do so,
  // type:  usleep(3 * microsecond);
  void animate(ostream& output, int top, int endIter, int playback) {
    unsigned int microsecond = 50000 / playback;  // divide by playback
    // (decrease delay)

    if (endIter == -1) {  // check if endIter = -1
      endIter = this->size-1;  // sets to entire size of barcharts
    }

    for (int i = 0; i <= endIter; i++) {  // loop through barcharts
      usleep(3 * microsecond);
      output << CLEARCONSOLE;

      output << WHITE;
      output << this->title << endl;
      output << WHITE;
      output << this->source << endl;
      
      barcharts[i].graph(cout, colorMap, top);
      output << WHITE;
      output << this->xlabel << endl;
      output << "Frame: " << barcharts[i].getFrame() << endl;
    }
  }

  //
  // Public member function.
  // Returns the size of the BarChartAnimate object.
  //
  int getSize() {
    return this->size;
  }

  //
  // Public member function.
  // Returns BarChart element in BarChartAnimate.
  // This gives public access to BarChart stored in the BarChartAnimate.
  // If i is out of bounds, throw an out_of_range error message:
  // "BarChartAnimate: i out of bounds"
  //
  BarChart& operator[](int i) {
    if (i < 0 || i >= size) {  // check if i out of bounds
      throw out_of_range("BarChartAnimate: i out of bounds");
    }

    return barcharts[i];  // return barcharts @ i
  }
};