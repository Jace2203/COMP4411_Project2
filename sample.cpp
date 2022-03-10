// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"
#include "complexshape.h"

#include <cmath>

class Point;

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
public:
    SampleModel(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label) { }

    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{ 
    return new SampleModel(x,y,w,h,label); 
}

Point* ctrl = nullptr;	// ctrl points of circle curve
Point* pts = nullptr;	// actual circle curve
Point* ctrl2 = nullptr;	// ctrl points of path curve
Point* path = nullptr;	// actual path curve
Point** draw_pts = nullptr;
int num_point = 0;
int num_ctrl2 = 0;

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
    ModelerView::draw();

	// // draw the floor
	// setAmbientColor(.1f,.1f,.1f);
	// setDiffuseColor(COLOR_RED);
	// glPushMatrix();
	// glTranslated(-5,0,-5);
	// drawBox(10,0.01f,10);
	// glPopMatrix();

	// // draw the sample model
	// setAmbientColor(.1f,.1f,.1f);
	// setDiffuseColor(COLOR_GREEN);
	// glPushMatrix();
	// glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

	// 	glPushMatrix();
	// 	glTranslated(-1.5, 0, -2);
	// 	glScaled(3, 1, 4);
	// 	drawBox(1,1,1);
	// 	glPopMatrix();

	// 	// draw cannon
	// 	glPushMatrix();
	// 	glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
	// 	glRotated(-90, 1.0, 0.0, 0.0);
	// 	drawCylinder(VAL(HEIGHT), 0.1, 0.1);

	// 	glTranslated(0.0, 0.0, VAL(HEIGHT));
	// 	drawCylinder(1, 1.0, 0.9);

	// 	glTranslated(0.0, 0.0, 0.5);
	// 	glRotated(90, 1.0, 0.0, 0.0);
	// 	drawCylinder(4, 0.1, 0.2);
	// 	glPopMatrix();

	// glPopMatrix();
	// drawTurret();

	int init = 0;

    num_point = 9;

	double l = 1,
	       h = 1;

	ctrl = new Point[num_point];
	ctrl[0] = Point(+0.0, +0.0 * 1.15, +0.0);
	ctrl[1] = Point(-1.0, +0.0 * 1.15, +0.0);
	ctrl[2] = Point(-1.0, +1.0 * 1.15, +0.0);
	ctrl[3] = Point(-1.0, +2.0 * 1.15, +0.0);
	ctrl[4] = Point(+0.0, +2.0 * 1.15, +0.0);
	ctrl[5] = Point(+1.0, +2.0 * 1.15, +0.0);
	ctrl[6] = Point(+1.0, +1.0 * 1.15, +0.0);
	ctrl[7] = Point(+1.0, +0.0 * 1.15, +0.0);
	ctrl[8] = Point(+0.0, +0.0 * 1.15, +0.0);

	num_ctrl2 = 4;

	ctrl2 = new Point[num_ctrl2];

	l = 0.75;
	h = 1;

	ctrl2[0] = Point(+0.0, +3.0, +0.0);
	ctrl2[1] = Point(+0.0, +1.0, +0.0);
	ctrl2[2] = Point(+3.0, +2.0, +0.0);
	ctrl2[3] = Point(+3.0, +0.0, +0.0);

	int num_t = 101;

	//setcircle(3, 1);

	calpoint(ctrl, &pts, num_point, num_t);
	calpoint(ctrl2, &path, num_ctrl2, num_t);

	init = 1;

	if (init)
	{

		draw_pts = new Point* [num_t];
		for(int i = 0; i < num_t; ++i)
		{
			draw_pts[i] = new Point[num_t];
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
			// theta = atan(dy / dx), theta2 = atan(dz / dx);

			// if (dx > 0 && dy > 0)
			// 	theta = M_PI/2 - theta;
			// else if (dx > 0 && dy < 0)
			// 	theta = M_PI/2 - theta;
			// else if (dx < 0 && dy < 0)
			// 	theta = 3*M_PI/2 - theta;
			// else if (dx < 0 && dy > 0)
			// 	theta = 3*M_PI/2 - theta;

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

	for(int i = 0; i < num_point; ++i)
	{
		glPushMatrix();
		glTranslated(ctrl[i].x, ctrl[i].y, ctrl[i].z);
		drawSphere(0.1);
		glPopMatrix();
	}

	for(int i = 0; i < num_ctrl2; ++i)
	{
		glPushMatrix();
		glRotated(90, 0, 1, 0);
		glTranslated(ctrl2[i].x, ctrl2[i].y, ctrl2[i].z);
		drawSphere(0.1);
		glPopMatrix();
	}

	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < num_t; ++i)
		glVertex3d(pts[i].x, pts[i].y, pts[i].z);
	glEnd();

	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < num_t; ++i)
		glVertex3d(path[i].x, path[i].y, path[i].z);
	glEnd();
	glPopMatrix();

	if (!VAL(MODE))
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
			if (i % 3 == 0)
				setDiffuseColor(1, 0, 0);
			else if (i % 3 == 1)
				setDiffuseColor(0, 1, 0);
			else
				setDiffuseColor(0, 0, 1);
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

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
    controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);
	controls[MODE] = ModelerControl("Mode", 0, 1, 1, 0);

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
