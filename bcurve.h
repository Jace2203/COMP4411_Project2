#ifndef BCURVE_H
#define BCURVE_H

#include "vec.h"
#include "modelerdraw.h"

class Bcurve
{
    
public:

    int num_point;
    int num_t;

    Vec3d* ctrl;
    Vec3d* curve;

    Bcurve(int num_point, int num_t, Vec3d* pts);
    ~Bcurve();
};

#endif