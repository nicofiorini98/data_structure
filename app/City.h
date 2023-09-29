#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <string>
#include <cmath>




class City {

    // chiave della citta
    std::string name;
    double latitude;
    double longitude;

  public:

    City(){
        this->name      = "";
        this->latitude  = 0;
        this->longitude = 0;
    }
    
    City(const std::string name):name(name){}
    
    City(const std::string &name, double lat, double lon)
        : name(name), latitude(lat), longitude(lon) {}

    
    std::string getName()const {return this->name;}
    double getLatitude()const {return this->latitude;}
    double getLongitude()const{return this->longitude;}
    // operator =
    City &operator=(const City &city) {
        this->latitude = city.latitude;
        this->longitude = city.longitude;
        this->name = city.name;
        return *this;
    }

    // operator ==
    bool operator==(const City &city) const { return this->name == city.name; }

    // operator<
    bool operator<(const City &city) const { return this->name < city.name; }

    // operator<=
    bool operator<=(const City &city) const { return this->name <= city.name; }

    // operator>
    bool operator>(const City &city) const { return this->name > city.name; }

    // operator>=
    bool operator>=(const City &city) const { return this->name >= city.name; }

    // operator!=
    bool operator!=(const City &city) const { return this->name != city.name; }

    // operator<<
    friend std::ostream &operator<<(std::ostream &os, City city) {
        // os << c.key;
        // os << city.name << ";" << city.latitude << ";" << city.longitude;
        os << city.name;
        return os;
    }

    // operator >>
    friend std::istream &operator>>(std::istream &is, City& city) {
        
        std::string line;
        std::getline(is,line,';');
        city.name = line;

        std::getline(is,line,';');
        city.latitude = std::stod(line);
        std::getline(is,line);
        city.longitude = std::stod(line);
        
        return is;
    }
};

constexpr double kEarthRadiusKm = 6371.0; // earth's radius in kilometers
constexpr double degreesToRadians(double degrees) {
    return (degrees * M_PI) / 180.0;
}

inline double calculateDistance(const City& city1, const City& city2) {
    double lat1 = degreesToRadians(city1.getLatitude());
    double lon1 = degreesToRadians(city1.getLongitude());
    double lat2 = degreesToRadians(city2.getLatitude());
    double lon2 = degreesToRadians(city2.getLongitude());

    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1) * cos(lat2) * sin(dLon / 2) * sin(dLon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return kEarthRadiusKm * c;
}

#endif