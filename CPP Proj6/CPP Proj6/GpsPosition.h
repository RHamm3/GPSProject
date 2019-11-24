#ifndef GPSPOSITION_H
#define GPSPOSITION_H

class GpsPosition {
private:
	double latitude;
	double longitude;
	unsigned long timeSeconds;
public:
	GpsPosition();
	GpsPosition(double latitude, double longitude, unsigned long timeSeconds);
	double GetLatitude();
	double GetLongitude();
	unsigned long GetTime();
	void SetLatitude(double latitude);
	void SetLongitude(double longitude);
	void SetTime(double timeSeconds);
	double CalcDistanceKmTo(GpsPosition toPosition);

};

#endif 

