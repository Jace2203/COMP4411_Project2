#include "ik.h"

#include <math.h>

#  ifndef M_PI
#    define M_PI            3.14159265358979323846
#    define M_PI_2          1.57079632679489661923
#    define M_PI_4          0.78539816339744830962
#    define M_1_PI          0.31830988618379067154
#    define M_2_PI          0.63661977236758134308
#  endif // !M_PI

void LegIK(double* lengths, double* angles, double** limits, const Vec3d& target)
{
    int count = 0;

    // Init value
    Vec3d thigh = getRotY(angles[1]) * getRotX(angles[0]) * Vec3d(0.0, -lengths[0], 0.0);
    Vec3d leg = getRotY(angles[1]) * getRotX(angles[0] + angles[2]) * Vec3d(0.0, -lengths[1], 0.0);
    Vec3d whole = thigh + leg;

    while (count < 10 && (whole - target).length2() > 0.0001)
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
        temp_target = target;
        leg = temp_target - thigh;
        leg.normalize();
        leg *= lengths[1];


        // double* thigh_angles = getAngles(thigh);
        // double* leg_angles = getAngles(leg);

        // if (thigh_angles[0] > limits[0][1]) thigh_angles[0] = limits[0][1];
        // if (thigh_angles[0] < limits[0][0]) thigh_angles[0] = limits[0][0];
        
        // if (thigh_angles[1] > limits[1][1]) thigh_angles[0] = limits[1][1];
        // if (thigh_angles[1] < limits[1][0]) thigh_angles[0] = limits[1][0];

        // leg_angles[0] = thigh_angles[0] - leg_angles[0];
        
        // if (leg_angles[0] > limits[2][1]) leg_angles[0] = limits[2][1];
        // if (leg_angles[0] < limits[2][0]) leg_angles[0] = limits[2][0];

        // angles[0] = thigh_angles[0];
        // angles[1] = thigh_angles[1];
        // angles[2] = leg_angles[0];

        // // std::cout << angles[0] << " " << angles[1] << " " << angles[2] << std::endl;
        // thigh = getRotY(angles[1]) * getRotX(angles[0]) * Vec3d(0.0, -lengths[0], 0.0);
        // leg = getRotY(angles[1]) * getRotX(angles[0] + angles[2]) * Vec3d(0.0, -lengths[1], 0.0);

        // delete[] thigh_angles;
        // delete[] leg_angles;

        whole = thigh + leg;
        count++;
    }

    std::cout << thigh << " " << leg << std::endl;

    double* thigh_angles = getAngles(thigh);
    double* leg_angles = getAngles(leg);

    if (thigh_angles[0] > limits[0][1]) thigh_angles[0] = limits[0][1];
    if (thigh_angles[0] < limits[0][0]) thigh_angles[0] = limits[0][0];
    
    if (thigh_angles[1] > limits[1][1]) thigh_angles[1] = limits[1][1];
    if (thigh_angles[1] < limits[1][0]) thigh_angles[1] = limits[1][0];

    leg_angles[0] = thigh_angles[0] + leg_angles[0] + leg_angles[0];
    
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

    if (abs(vec[0] - 0) < 0.0001)
        result[1] = 0;
    else
        result[1] = atan2(vec[2], vec[0]) / M_PI * 180;

    vec = getRotY(-result[1]) * vec;
    result[0] = atan2(-vec[2], -vec[1]) / M_PI * 180;

    return result;
}

Mat4d getRotX(double angle)
{
    double t = angle * M_PI / 180;
    Mat4d result;

    result[0][0] = 1;
    result[1][1] = cos(t);
    result[1][2] = -sin(t);
    result[2][1] = sin(t);
    result[2][2] = cos(t);

    return result;
}

Mat4d getRotY(double angle)
{
    double t = angle * M_PI / 180;
    Mat4d result;

    result[0][0] = cos(t);
    result[0][2] = sin(t);
    result[1][1] = 1;
    result[2][0] = -sin(t);
    result[2][2] = cos(t);

    return result;
}