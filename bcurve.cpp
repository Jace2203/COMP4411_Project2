#include "bcurve.h"

Bcurve::Bcurve(int num_point, int num_t, Vec3d* pts): num_point(num_point), num_t(num_t)
{
    ctrl = new Vec3d[num_point];
    for(int i = 0; i < num_point; ++i)
        ctrl[i] = pts[i];

    calpoint(ctrl, &curve, num_point, num_t);
}

Bcurve::~Bcurve()
{
    // if (ctrl) delete [] ctrl;
    // if (curve) delete [] curve;
}