#include "ik.h"

#include "mat.h"

#include <math.h>

void LegIK(double* lengths, double* angles, double** limits, const Vec3d& target)
{
    int count = 0;

    // Init value
    Vec3d thigh = Mat4d::createRotation(angles[1], 0.0, 1.0, 0.0) * Mat4d::createRotation(angles[0], 1.0, 0.0, 0.0) * Vec3d(0.0, -lengths[0], 0.0);
    Vec3d leg = Mat4d::createRotation(angles[1], 0.0, 1.0, 0.0) * Mat4d::createRotation(angles[0] - angles[2], 1.0, 0.0, 0.0) * Vec3d(0.0, -lengths[1], 0.0);
    Vec3d whole = thigh + leg;

    while (count < 100 && (whole - target).length() > 0.01)
    {
        Vec3d temp_target = target;

        // Forward
        Vec3d temp_leg = temp_target - thigh;
        temp_leg.normalize();
        temp_leg *= lengths[1];

        temp_target = temp_target - temp_leg;
        thigh = temp_target;
        thigh.normalize();
        thigh *= lengths[0];

        // Backward
        leg = temp_target - thigh;
        leg.normalize();
        leg *= lengths[1];

        whole = thigh + leg;
        count++;
    }

    double* thigh_angles = getAngles(thigh);
    double* leg_angles = getAngles(leg);

    if (thigh_angles[0] > limits[0][1]) thigh_angles[0] = limits[0][1];
    if (thigh_angles[0] < limits[0][0]) thigh_angles[0] = limits[0][0];
    
    if (thigh_angles[1] > limits[1][1]) thigh_angles[0] = limits[1][1];
    if (thigh_angles[1] < limits[1][0]) thigh_angles[0] = limits[1][0];

    leg_angles[0] = thigh_angles[0] - leg_angles[0];
    
    if (leg_angles[0] > limits[2][1]) leg_angles[0] = limits[2][1];
    if (leg_angles[0] < limits[2][0]) leg_angles[0] = limits[2][0];

    angles[0] = thigh_angles[0];
    angles[1] = thigh_angles[1];
    angles[2] = leg_angles[0];

    // std::cout << angles[0] << " " << angles[1] << " " << angles[2] << std::endl;

    delete[] thigh_angles;
    delete[] leg_angles;
}

double* getAngles(Vec3d vec)
{
    double* result = new double[2];

    result[0] = asin(vec[1] / vec.length());
    result[1] = atan2(vec[2], vec[0]);

    return result;
}