#include <iostream>
#include "GpsPosition.h"
#include "velociplotter.h"

int main(int argc, char* argv[]) {
	
	VelociPlotter data;
	

	data.ReadFile(argv[1]);
	data.speedCalc();
	data.gpsPlotDataFile(argv[2]);

	return 0;
}