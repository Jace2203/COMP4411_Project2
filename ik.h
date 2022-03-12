#ifndef IK_H
#define IK_H

#include "vec.h"
#include "mat.h"

void LegIK(double* lengths, double* angles, double** limits, const Vec3d& target);

double* getAngles(Vec3d vec);

Mat4d getRotX(double angle);
Mat4d getRotY(double angle);

#endif