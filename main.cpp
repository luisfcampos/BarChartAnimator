// Bar Chart Animation
//
// This application uses BarChartAnimate (which uses BarChart, which uses Bar)
// to produce an animated bar chart.
//
// Bar Chart Animator:
// Takes in input from user as follows:
// filename (string) w/o '.txt'
// top value (int)
// playback speed (int)
//
// The program then automatically animates the bars taken in from the file inputted.
// 

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;


int main() {
  
	string filename = "";
  cout << "Welcome to the Bar Chart Animator!" << endl;
  
  cout << "\nEnter filename(w/o file extension) to begin: ";
  cin >> filename;
  string filename2 = filename;
  filename += ".txt";
	
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
	while (!inFile.eof()) {
		bca.addFrame(inFile);
	}
  
	int top = 10;
  cout << "Enter top amount of '" << filename2 << "' you would like displayed: ";
  cin >> top;
  
  int playback = 1;
  cout << "Enter a playback speed(1-4x): ";
  cin >> playback;
  if (playback < 1 || playback > 4) { // makes sure playback speed input is
    // between 1-4
    cout << "Invalid playback, setting playback to default (1x)" << endl;
    playback = 1;
  }
  
	bca.animate(cout, top, -1, playback);
	// cout << CLEARCONSOLE;
	usleep(15 * 50000);	// delay on last frame
	cout << endl;
	cout << "Thanks for running Bar Chart Animator!" << endl;
	cout << "Press 'RUN' to start over." << endl;

    return 0;
}
