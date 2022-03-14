#include "surface.h"
#include "gl.h"

Surface::Surface(int num_t, bcurve* surface, bcurve* path):num_t(num_t), surface(surface), path(path)
{
    draw_pts = new Vec3d* [num_t];
    for(int i = 0; i < num_t; ++i)
    {
        draw_pts[i] = new Vec3d[num_t];
        int previous, next;
        if (i == 0)
        {
            previous = 0;
            next = 1;
        }
        else if (i == num_t)
        {
            previous = num_t - 1;
            next = num_t;
        }
        else
        {
            previous = i - 1;
            next = i + 1;
        }

        double dx = path[next].x - path[previous].x, dy = path[next].y - path[previous].y, dz = path[next].z - path[previous].z;
        double theta, theta2 = 0;

        theta = acos(-dy/(sqrt(pow(dx, 2)+pow(dy, 2))));

        if (dx < 0)
            theta = 2*M_PI - theta;

        theta = theta - M_PI/2;

        //printf("%1f\n", theta*180/M_PI);
        for(int j = 0; j < num_t; ++j)
        {
            double x = pts[j].x, y = pts[j].y, z = pts[j].z;
            double x1 = x, y1 = y*cos(theta) - z*sin(theta), z1 = y*sin(theta)+ z*cos(theta);  // x axis rotate
            double x2 = x1*cos(theta2)+ z1*sin(theta2), y2 = y1, z2 = -x1*sin(theta2)+ z1*cos(theta2);  //y axis rotate
            //x2 = x; y2 = y; z2 = z;
            
            draw_pts[i][j].x = x2+path[i].z;
            draw_pts[i][j].y = y2+path[i].y;
            draw_pts[i][j].z = z2-path[i].x;
        }
    }
}

Surface::~Surface()
{
    if (surface) delete [] surface;
    if (path) delete [] path;

    for(int i = 0; i < num_t; ++i)
        if (draw_pts[i]) delete[] draw_pts[i];
}

Surface::void draw(int mode)
{
	if (mode)
	{
		for(int i = 0; i < num_t; ++i)
		{
			glBegin(GL_LINE_STRIP);
			for(int j = 0; j < num_t; ++j)
				glVertex3d(draw_pts[i][j].x, draw_pts[i][j].y, draw_pts[i][j].z);
			glEnd();
		}
	}
	else
	{
		for(int i = 0; i < num_t-1; ++i)
		{
			glBegin(GL_TRIANGLE_STRIP);
			for(int j = 0; j < num_t; ++j)
			{
				glVertex3d(draw_pts[i][j].x, draw_pts[i][j].y, draw_pts[i][j].z);
				glVertex3d(draw_pts[i+1][j].x, draw_pts[i+1][j].y, draw_pts[i+1][j].z);
			}
			glEnd();
		}
	}
}