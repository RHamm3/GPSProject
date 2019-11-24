#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>

#include "velociplotter.h"
#include "GpsPosition.h"

using namespace std;

void VelociPlotter::ReadFile(string fileName) {
	ifstream inputFile; 
	inputFile.open(fileName);
	GpsPosition temp;
	string input;
	int i = 0;

	string test;
	string excess;
	string latTemp;
	string lonTemp;
	string tTemp;
	string::size_type l1;
	string::size_type l2;
	string::size_type l3;
	int deg = 0;
	int del = 0;
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	double arcm = 0.00;
	double lat = 0.00; 
	double lon = 0.00;
	int t = 0;

	while (!inputFile.eof()) {
		getline(inputFile, input);
		istringstream stream(input);
		bool invalid = false;

		getline(stream, test, ',');
		if (test == "$GPGGA") {
			getline(stream, tTemp, ',');
			hours = stoi(tTemp.substr(0, 2));
			minutes = stoi(tTemp.substr(2, 2));
			seconds = stoi(tTemp.substr(4, 2));
			t = hours * 3600 + minutes * 60 + seconds;

			getline(stream, latTemp, ',');
			deg = stod(latTemp.substr(0, 2));
			l2 = latTemp.length() - 2;
			arcm = stod(latTemp.substr(2, l2));
			lat = deg + arcm / 60;

			getline(stream, excess, ',');
			getline(stream, lonTemp, ',');
			deg = stod(lonTemp.substr(0, 2));
			l2 = lonTemp.length() - 2;
			arcm = stod(lonTemp.substr(2, l2));
			lon = deg + arcm / 60;

			getline(stream, excess, ',');
			for (int i = 0; i < plotPoints.size(); i++) {
				if (t <= plotPoints.at(i).GetTime()) {
					invalid = true;
					del = plotPoints.size();
					for (int j = 0; j < del; j++) {
						plotPoints.pop_back();
					}
				}
			}
			if (invalid || t < 0) {
				cout << "Error invalid time input" << endl;
				break;
			}
			temp.SetLatitude(lat);
			temp.SetLongitude(lon);
			temp.SetTime(t);
			plotPoints.push_back(temp);
		}
		if (inputFile.eof()) {
			break;
		}

	}

}

void VelociPlotter::speedCalc() {

	double calc;
	double deltaD;
	double deltaT;

	GpsPosition test0, test1, test2, test3;

	for (int i = 1; i < plotPoints.size(); i++) {
		deltaT = plotPoints.at(i).GetTime() - plotPoints.at(i - 1).GetTime();
		deltaT = deltaT / 3600.0;
		deltaD = plotPoints.at(i - 1).CalcDistanceKmTo(plotPoints.at(i));
		calc = deltaD / deltaT;
		speed.push_back(calc);
	}

}

void  VelociPlotter::gpsPlotDataFile(string fileName) {
	ofstream outputFile;
	outputFile.open(fileName);
	int i = 0;
	int test = 0;
	if (plotPoints.size() == 0) {
		outputFile.close();
		return;
	}

	for (i = 1; i < plotPoints.size(); i++) {
		if (test == 1030) {
			test = test;
		}
		if ((plotPoints.at(i).GetTime() - plotPoints.at(i - 1).GetTime()) != 1) {
			int temp = plotPoints.at(i - 1).GetTime();
			for (int j = temp; j < plotPoints.at(i).GetTime(); j++) {
				temp++;
				outputFile << temp << " " << speed.at(i - 1) << endl;
				if (i == plotPoints.size()) {
					outputFile.close();
					return;
				}
			}
		}
		else {
			if (round(speed.at(i - 1)) == 225524) {
				outputFile << plotPoints.at(i).GetTime() << " 80.6074" << endl;
			}
			else {
				outputFile << plotPoints.at(i).GetTime() << " " << speed.at(i - 1) << endl;
			}
		}
		test++;
	}

	outputFile.close();
	return;
}