#include <math.h>
#include "GpsPosition.h"


GpsPosition::GpsPosition() {
	latitude = 0;
	longitude = 0;
	timeSeconds = -1;
}

GpsPosition::GpsPosition(double _latitude, double _longitude, unsigned long _timeSeconds) {
	latitude = _latitude;
	longitude = _longitude;
	timeSeconds = _timeSeconds;
}

double GpsPosition::GetLatitude() {
	return latitude;
}

double GpsPosition::GetLongitude() {
	return longitude;
}

unsigned long GpsPosition::GetTime() {
	return timeSeconds;
}

void GpsPosition::SetLatitude(double _latitude) {
	latitude = _latitude;
}

void GpsPosition::SetLongitude(double _longitude) {
	longitude = _longitude;
}

void GpsPosition::SetTime(double _timeSeconds) {
	timeSeconds = _timeSeconds;
}

double GpsPosition::CalcDistanceKmTo(GpsPosition toPosition) {

	const double EarthRadiusKm = 6371.0;
	const double PI = 3.14159265358979323846;
	double fromLatitudeRad;
	double fromLongitudeRad;
	double toLatitudeRad;
	double toLongitudeRad;
	double deltaLatitude;
	double deltaLongitude;
	double a;
	double c;

	// Convert to radians
	fromLatitudeRad = PI * this->GetLatitude() / 180.0;
	fromLongitudeRad = PI * this->GetLongitude() / 180.0;
	toLatitudeRad = PI * toPosition.GetLatitude() / 180.0;
	toLongitudeRad = PI * toPosition.GetLongitude() / 180.0;

	// Calculate delta for latituce and longitude
	deltaLatitude = toLatitudeRad - fromLatitudeRad;
	deltaLongitude = toLongitudeRad - fromLongitudeRad;
	
	// Calculate great-circle distance using haversine formula
	a = (sin(deltaLatitude / 2) * sin(deltaLatitude / 2)) +
	(sin(deltaLongitude / 2) * sin(deltaLongitude / 2) *
	cos(fromLatitudeRad) * cos(toLatitudeRad));
	c = 2 * atan2(sqrt(a), sqrt(1 - a));
	return EarthRadiusKm * c;

}