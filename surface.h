#include "bcurve.h"

class bcurve;

class Surface
{
public:

    int num_t;
    bcurve* surface;
    bcurve* path;

    Vec3** draw_pts;

    Surface(int num_t, bcurve* surface, bcurve* path);
    ~Surface();

    void draw();
}