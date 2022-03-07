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
Point** pts = nullptr;	// actual circle curve
Point* ctrl2 = nullptr;	// ctrl points of path curve
Point** path = nullptr;	// actual path curve
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

	if (VAL(NOP) != num_point)
	{
		if (ctrl)
		{
			Point* temp = new Point[int(VAL(NOP))];

			double x = 1, y = 0, z = 0,
				   x1 = x *cos(atan(dzpts(99))), z1 = -x*sin(atan(dzpts(99))),  // y axis rotate
				   theta = atan(dypts(99)),
				   x2 = x1 *cos(theta), y2 = x1*sin(theta);  //z axis rotate
			for(int i = 0; i < VAL(NOP); ++i)
			{
				if (i < num_point)
					temp[i] = ctrl[i];
				else
				{
					temp[i].x = temp[i-1].x+x2;
					temp[i].y = temp[i-1].y+y2;
					temp[i].z = temp[i-1].z;
				}
			}

			ctrl = temp;
		}
		else
		{
			num_point = 3;

			ctrl = new Point[int(VAL(NOP))];
			// for(int i = 0; i < int(VAL(NOP)); ++i)
			// 	ctrl[i].x = double(i);
			ctrl[0] = Point(0, 0, 0);
			ctrl[1] = Point(1, 1, 0);
			ctrl[2] = Point(2, 0, 0);

			ctrl2 = new Point[int(VAL(NOP))];
			// for(int i = 0; i < int(VAL(NOP)); ++i)
			// 	ctrl2[i].x = double(i);
			ctrl2[0] = Point(0, 0, 0);
			ctrl2[1] = Point(1, -1, 0);
			ctrl2[2] = Point(2, 0, 0);
		}

		// num_point = VAL(NOP);

		pts = new Point*[num_point];
		for(int i = 0; i < num_point; ++i)
			pts[i] = new Point[100];

		path = new Point*[num_point];
		for(int i = 0; i < num_point; ++i)
			path[i] = new Point[100];

		init = 1;
	}

	if (VAL(A) || init)
	{
		if (VAL(P) < num_point)
		{
			ctrl[int(VAL(P))].x = VAL(X);
			ctrl[int(VAL(P))].y = VAL(Y);
			ctrl[int(VAL(P))].z = VAL(Z);
		}

		double t;	
		for(int j = 0; j < num_point-1; ++j)
		{
			t = 0;
			for(int i = 0; i < 100; ++i)
			{
				pts[j][i].x = (1-t)*ctrl[j].x+t*ctrl[j+1].x;
				pts[j][i].y = (1-t)*ctrl[j].y+t*ctrl[j+1].y;
				pts[j][i].z = (1-t)*ctrl[j].z+t*ctrl[j+1].z;
				path[j][i].x = (1-t)*ctrl2[j].x+t*ctrl2[j+1].x;
				path[j][i].y = (1-t)*ctrl2[j].y+t*ctrl2[j+1].y;
				path[j][i].z = (1-t)*ctrl2[j].z+t*ctrl2[j+1].z;
				t += 0.01;
			}
		}

		for(int i = num_point-2; i > 0; --i)
			for(int j = 0; j < i; ++j)
			{
				t = 0;
				for(int k = 0; k < 100; ++k)
				{
					pts[j][k].y = (1-t)*pts[j][k].y+t*pts[j+1][k].y;
					pts[j][k].z = (1-t)*pts[j][k].z+t*pts[j+1][k].z;
					pts[j][k].x = (1-t)*pts[j][k].x+t*pts[j+1][k].x;
					path[j][k].y = (1-t)*path[j][k].y+t*path[j+1][k].y;
					path[j][k].z = (1-t)*path[j][k].z+t*path[j+1][k].z;
					path[j][k].x = (1-t)*path[j][k].x+t*path[j+1][k].x;
					t += 0.01;
				}
			}

		draw_pts = new Point* [100];
		for(int i = 0; i < 100; ++i)
		{
			draw_pts[i] = new Point[100];
			for(int j = 0; j < 100; ++j)
			{
				double x = pts[0][j].x, y = pts[0][j].y, z = pts[0][j].z,
					   x1 = x, y1 = y*cos(atan(dypath(i))) - z*sin(atan(dypath(i))), z1 = y*sin(atan(dypath(i)))+ z*cos(atan(dypath(i))),  // x axis rotate
					   theta = atan(dzpath(i)),
					   x2 = x1*cos(theta)+ z1*sin(theta), y2 = y1, z2 = -x1*sin(theta)+ z1*cos(theta);  //y axis rotate
				
				//printf("%1f %1f\n", atan(dypath(j)), theta);
				draw_pts[i][j].x = x2+path[0][i].z;
				draw_pts[i][j].y = y2+path[0][i].y;
				draw_pts[i][j].z = z2-path[0][i].x;
			}
		}
	}

	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < 100; ++i)
		glVertex3d(path[0][i].x, path[0][i].y, path[0][i].z);
	glEnd();
	glPopMatrix();

	for(int i = 0; i < num_point; ++i)
	{
		glPushMatrix();
		glTranslated(ctrl[i].x, ctrl[i].y, ctrl[i].z);
		drawSphere(0.1);
		glPopMatrix();
	}

	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < 100; ++i)
		glVertex3d(pts[0][i].x, pts[0][i].y, pts[0][i].z);
	glEnd();

	for(int i = 0; i < 99; ++i)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(int j = 0; j < 100; ++j)
		{
			glVertex3d(draw_pts[i][j].x, draw_pts[i][j].y, draw_pts[i][j].z);
			glVertex3d(draw_pts[i+1][j].x, draw_pts[i+1][j].y, draw_pts[i+1][j].z);
		}
		glEnd();
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
	controls[NOP] = ModelerControl("Num", 2, 6, 1, 4);
	controls[P] = ModelerControl("Points", 0, 8, 1, 0);
	controls[C] = ModelerControl("Circle", 0, 1, 1, 1);
	controls[X] = ModelerControl("NewX", -4, 4, 1, 0);
	controls[Y] = ModelerControl("NewY", -4, 4, 1, 0);
	controls[Z] = ModelerControl("NewZ", -4, 4, 1, 0);
	controls[A] = ModelerControl("Activate", 0, 1, 1, 0);


    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
