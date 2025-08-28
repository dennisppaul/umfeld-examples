#pragma once
#include "Umfeld.h"

using namespace umfeld;

class Record {
public:
    std::string name;
    float       mpg;
    int         cylinders;
    float       displacement;
    float       horsepower;
    float       weight;
    float       acceleration;
    int         year;
    float       origin;

    Record() = default; //@diff(default_constructor)
    Record(std::vector<std::string> pieces) {
        name         = pieces[0];
        mpg          = atof(pieces[1].c_str()); //@diff(data_conversion)
        cylinders    = atoi(pieces[2].c_str()); //@diff(data_conversion)
        displacement = atof(pieces[3].c_str()); //@diff(data_conversion)
        horsepower   = atof(pieces[4].c_str()); //@diff(data_conversion)
        weight       = atof(pieces[5].c_str()); //@diff(data_conversion)
        acceleration = atof(pieces[6].c_str()); //@diff(data_conversion)
        year         = atoi(pieces[7].c_str()); //@diff(data_conversion)
        origin       = atof(pieces[8].c_str()); //@diff(data_conversion)
    }
};
