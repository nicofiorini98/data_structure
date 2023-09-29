#ifndef DISTANCE_CITY_H
#define DISTANCE_CITY_H

#include <iostream>
#include <string>
#include <cmath>
#include "City.h"


class DistanceCity {

    // chiave della citta
	City city;
	double distance;
  public:

    DistanceCity(){
        City city;
        distance = 10000;
    }
    
    DistanceCity(const std::string name): city({name}){}
    
    DistanceCity(const std::string name,double distance):city({name}),distance(distance){}
    
    DistanceCity(double distance,City city)
        : distance(distance), city(city) {}

    
    // std::string getName()const {return this->name;}
    double getDistance()const {return this->distance;}
    City getCity()const {return this->city;}
	
    // operator =
    DistanceCity &operator=(const DistanceCity &distanceCity) {
        this->distance= distanceCity.distance;
        this->city = distanceCity.city;
        return *this;
    }

    // operator ==
    bool operator==(const DistanceCity &city) const { return this->distance == city.distance; }

    // operator<
    bool operator<(const DistanceCity &city) const { return this->distance < city.distance; }

    // operator<=
    bool operator<=(const DistanceCity &city) const { return this->distance <= city.distance; }

    // operator>
    bool operator>(const DistanceCity &city) const { return this->distance > city.distance; }

    // operator>=
    bool operator>=(const DistanceCity &city) const { return this->distance >= city.distance; }

    // operator!=
    bool operator!=(const DistanceCity &city) const { return this->distance != city.distance; }

};


#endif