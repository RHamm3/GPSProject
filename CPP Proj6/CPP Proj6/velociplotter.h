#ifndef VELOCIPLOTTER_H
#define VELOCIPLOTTER_H

#include <vector>
#include <string>

#include "GpsPosition.h"

class VelociPlotter {
private:
	std::vector<GpsPosition> plotPoints;
	std::vector<double> speed;
public:
	void speedCalc();
	void ReadFile(std::string fileName);
	void gpsPlotDataFile(std::string fileName);
};

#endif

