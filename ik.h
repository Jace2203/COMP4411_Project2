#ifndef IK_H
#define IK_H

#include "vec.h"

void LegIK(double* lengths, double* angles, double** limits, const Vec3d& target);

double* getAngles(Vec3d vec);

#endif