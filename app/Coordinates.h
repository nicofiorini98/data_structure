#ifndef LOCATION_H 
#define LOCATION_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>


class Coordinates { 
	double latitude;
    double longitude;

public: 

	Coordinates(double lat, double lon) : latitude(lat), longitude(lon) {}

	double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }

    void setLatitude(double lat) {
        latitude = lat;
    }

    void setLongitude(double lon) {
        longitude = lon;
    }

    void display() const {
        std::cout << "Latitude: " << std::fixed << std::setprecision(6) << latitude << "°\n";
        std::cout << "Longitude: " << std::fixed << std::setprecision(6) << longitude << "°\n";
    }
};


inline double haversineDistance(const Coordinates& coord1, const Coordinates& coord2) {
    const double R = 6371.0; // Earth's radius in kilometers

    double lat1 = coord1.getLatitude();
    double lon1 = coord1.getLongitude();
    double lat2 = coord2.getLatitude();
    double lon2 = coord2.getLongitude();

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(lat1 * M_PI / 180.0) * std::cos(lat2 * M_PI / 180.0) *
               std::sin(dLon / 2) * std::sin(dLon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    double distance = R * c;
    return distance;
}

#endif /* LOCATION_H */
