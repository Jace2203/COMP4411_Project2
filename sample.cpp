// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"
#include "complexshape.h"
#include "drawbody.h"

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
    ModelerView::draw();

	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		int lod = int(VAL(LOD));
		// Torso
		glPushMatrix();
			glRotated(-90.0, 1.0, 0.0, 0.0);

			loadTexture("body2.bmp");
			glEnable(GL_TEXTURE_2D);

			drawTorso();

			glDisable(GL_TEXTURE_2D);

			if (lod > 0)
			{
				drawHead();

				drawArmL(VAL(L_UPPER_ARM_YROT), VAL(L_UPPER_ARM_ZROT), 45.0, 0.0, lod - 1);
				drawArmR(VAL(R_UPPER_ARM_YROT), VAL(R_UPPER_ARM_ZROT), 45.0, 0.0, lod - 1);
	
				loadTexture("leg.bmp");
				glEnable(GL_TEXTURE_2D);

				drawLegL(VAL(L_LEG_XROT));
				drawLegR(VAL(R_LEG_XROT));

				glDisable(GL_TEXTURE_2D);

				drawEquipment(VAL(BACK_YROT), VAL(L_EQUIP_YROT), VAL(R_EQUIP_YROT), VAL(L_TURRET_YROT), VAL(R_TURRET_YROT), VAL(L_TURRET_XROT), VAL(R_TURRET_XROT), lod);
			}

		glPopMatrix();

	glPopMatrix();


/*
	int init = 0;

    num_point = 4;

	ctrl = new Point[num_point];
	ctrl[0] = Point(+0.15, +1.0, +0.0);
	ctrl[1] = Point(+0.00, +0.8, +0.0);
	ctrl[2] = Point(+0.00, +0.35, +0.0);
	ctrl[3] = Point(-0.00, +0.0, +0.0);

	num_ctrl2 = 4;

	ctrl2 = new Point[num_ctrl2];

	ctrl2[0] = Point(+0.0, +0.0, +0.0);
	ctrl2[1] = Point(+0.0, +0.0, -0.3);
	ctrl2[2] = Point(+0.5, +0.0, -0.3);
	ctrl2[3] = Point(+0.5, +0.0, +0.0);

	int num_t = 101;

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

	// for(int i = 0; i < num_point; ++i)
	// {
	// 	glPushMatrix();
	// 	glTranslated(ctrl[i].x, ctrl[i].y, ctrl[i].z);
	// 	drawSphere(0.1);
	// 	glPopMatrix();
	// }

	// for(int i = 0; i < num_ctrl2; ++i)
	// {
	// 	glPushMatrix();
	// 	glRotated(90, 0, 1, 0);
	// 	glTranslated(ctrl2[i].x, ctrl2[i].y, ctrl2[i].z);
	// 	drawSphere(0.1);
	// 	glPopMatrix();
	// }

	// glBegin(GL_LINE_STRIP);
	// for(int i = 0; i < num_t; ++i)
	// 	glVertex3d(pts[i].x, pts[i].y, pts[i].z);
	// glEnd();

	// glPushMatrix();
	// glRotated(90, 0, 1, 0);
	// glBegin(GL_LINE_STRIP);
	// for(int i = 0; i < num_t; ++i)
	// 	glVertex3d(path[i].x, path[i].y, path[i].z);
	// glEnd();
	// glPopMatrix();

	if (!VAL(MODE))
	{
		for(int i = 1; i < num_t-1; ++i)
		{
			glBegin(GL_LINE_STRIP);
			for(int j = 0; j < num_t; ++j)
				glVertex3d(draw_pts[i][j].x, draw_pts[i][j].y, draw_pts[i][j].z);
			glEnd();
		}
	}
	else
	{
		for(int i = 1; i < num_t-1; ++i)
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
	*/
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];

	controls[LOD] = ModelerControl("Change Level of Detail", 0, 4, 1, 4);
	// Whole body
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);

	// Arm
	controls[L_UPPER_ARM_YROT] = ModelerControl("Left Upper Arm Y Rotation", 10, 135, 0.1f, 10);
	controls[L_UPPER_ARM_ZROT] = ModelerControl("Left Upper Arm Z Rotation", -45, 45, 0.1f, 0);
	controls[R_UPPER_ARM_YROT] = ModelerControl("Right Upper Arm Y Rotation", 10, 135, 0.1f, 10);
	controls[R_UPPER_ARM_ZROT] = ModelerControl("Right Upper Arm Z Rotation", -45, 45, 0.1f, 0);

	// Leg
	controls[L_LEG_XROT] = ModelerControl("Left Leg X Rotation", -30, 30, 0.1f, 0);
	controls[R_LEG_XROT] = ModelerControl("Right Leg X Rotation", -30, 30, 0.1f, 0);

	// Equipment
	controls[BACK_YROT] = ModelerControl("Back Equipment Y Rotation", -15, 15, 0.1f, 0);
	controls[L_EQUIP_YROT] = ModelerControl("Left Equipment Y Rotation", -15, 15, 0.1f, 0);
	controls[R_EQUIP_YROT] = ModelerControl("Right Equipment Y Rotation", -15, 15, 0.1f, 0);

	// Turret YROT
	controls[L_TURRET_YROT] = ModelerControl("Left Turret Y Rotation", -30, 225, 1, 0);
	controls[R_TURRET_YROT] = ModelerControl("Right Turret Y Rotation", -30, 225, 1, 0);

	// Turret XROT
	controls[L_TURRET_XROT] = ModelerControl("Left Turret X Rotation", 10, 85, 1, 36);
	controls[R_TURRET_XROT] = ModelerControl("Right Turret X Rotation", 10, 85, 1, 36);

	controls[MODE] = ModelerControl("Mode", 0, 1, 1, 0);

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
