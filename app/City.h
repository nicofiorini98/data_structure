#ifndef CITY_H
#define CITY_H

#include <string>
#include <iostream>

//example for a node 
class City{
	
public: 

	//chiave della citta
    int key;
    std::string name;

    City(){key=0;name="bolzano";}
    City(int _key,const std::string& _name): key(_key),name(_name){}

    //operator =
	City& operator=(City c){
        key = c.key;
        name = c.name;
        return *this;
    }

    //operator ==
    bool operator==(const City& _s) const {
        return key == _s.key;
    }

    //operator<
    bool operator<(const City& _s) const {
        return key < _s.key;
    }

    //operator<=
    bool operator<=(const City& _s) const {
        return key <= _s.key;
    }

    //operator>
    bool operator>(const City& _s) const {
        return key > _s.key;
    }

    //operator>=
    bool operator>=(const City& _s) const {
        return key >= _s.key;
    }

    //operator!=
    bool operator!=(const City& _s) const {
        return key != _s.key;
    }


    //operator<<
    friend std::ostream& operator<<(std::ostream& os, City c){
        // os << c.key;
        os << c.name;
        return os;
    }

    //operator >>
    friend std::istream& operator>>(std::istream& is, City c){
        //todo 
        //os << c.name;
        // os>>c.key;
        // is>>c.name;
        return is;
    }
};

#endif