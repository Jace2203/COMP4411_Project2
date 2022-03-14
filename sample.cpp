// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"
#include "complexshape.h"
#include "drawbody.h"
#include "camera.h"
#include "metaball.h"
#include "ik.h"

#include "cmath"
static GLfloat lightPosition0[] = { 4, 2, -4, 0 };
static GLfloat lightDiffuse0[]  = { 1,1,1,1 };
static int r = 4;

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
	double**	limits_L;
	double**	limits_R;
	double*		length;

	double*		angles_L;
	double*		angles_R;
	Vec3d*		last_target_L;
	Vec3d*		last_target_R;

public:
    SampleModel(int x, int y, int w, int h, char *label) 
    : ModelerView(x,y,w,h,label)
	{
		metaball_container = new MetaballContainer(2, 1, 0.05);
		for (int i = 0; i < 2; i++)
		{
			Metaball* metaball = new Metaball(Vec3d(0, 0, 0), 1);
			metaball_container->append(metaball);
		}
		
		limits_L = new double*[3];
		limits_R = new double*[3];
		for (int i = 0; i < 3; i++)
		{
			limits_L[i] = new double[2];
			limits_R[i] = new double[2];
		}

		limits_L[0][0] = -60;
		limits_L[0][1] = 50;
		limits_R[0][0] = -60;
		limits_R[0][1] = 50;
		
		limits_L[1][0] = -90;
		limits_L[1][1] = 0;
		limits_R[1][0] = 0;
		limits_R[1][1] = 90;
		
		limits_L[2][0] = 0;
		limits_L[2][1] = 140;
		limits_R[2][0] = 0;
		limits_R[2][1] = 140;

		last_target_L = new Vec3d(VAL(L_TARGET_X), VAL(L_TARGET_Y) - 0.9962, VAL(L_TARGET_Z));
		last_target_R = new Vec3d(VAL(R_TARGET_X), VAL(R_TARGET_Y) - 0.9962, VAL(R_TARGET_Z));

		length = new double[2];
		length[0] = 0.5;
		length[1] = 0.5;

		angles_L = new double[3];
		angles_L[0] = VAL(L_THIGH_XROT);
		angles_L[1] = VAL(L_THIGH_YROT);
		angles_L[2] = VAL(L_LEG_XROT);

		angles_R = new double[3];
		angles_R[0] = VAL(R_THIGH_XROT);
		angles_R[1] = VAL(R_THIGH_YROT);
		angles_R[2] = VAL(R_LEG_XROT);
	}

	~SampleModel()
	{
		for (int i = 0; i < 3; i++)
		{
			delete[] limits_L[i];
			delete[] limits_R[i];
		}

		delete[] limits_L;
		delete[] limits_R;
		delete[] length;

		delete[] angles_L;
		delete[] angles_R;

		delete last_target_L;
		delete last_target_R;
	}

    virtual void draw();
	MetaballContainer* metaball_container;
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{ 
    return new SampleModel(x,y,w,h,label); 
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
    ModelerView::draw();
	
	glEnable( GL_LIGHT0 );

	lightPosition0[0] = r * cos(VAL(LIGHT));
	lightPosition0[2] = r * sin(VAL(LIGHT));

	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition0 );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDiffuse0 );

	if (VAL(APPLY_IK))
	{
		if (*last_target_L != Vec3d(VAL(L_TARGET_X), VAL(L_TARGET_Y) - 0.9962, VAL(L_TARGET_Z)))
		{
			angles_L[0] = VAL(L_THIGH_XROT);
			angles_L[1] = VAL(L_THIGH_YROT);
			angles_L[2] = VAL(L_LEG_XROT);

			(*last_target_L)[0] = VAL(L_TARGET_X);
			(*last_target_L)[1] = VAL(L_TARGET_Y) - 0.9962;
			(*last_target_L)[2] = VAL(L_TARGET_Z);
			// std::cout << "L " << *last_target_L << std::endl;

			LegIK(length, angles_L, limits_L, *last_target_L);
			angles_L[1] *= -1;
		}

		if (*last_target_R != Vec3d(VAL(R_TARGET_X), VAL(R_TARGET_Y) - 0.9962, VAL(R_TARGET_Z)))
		{
			angles_R[0] = VAL(R_THIGH_XROT);
			angles_R[1] = VAL(R_THIGH_YROT);
			angles_R[2] = VAL(R_LEG_XROT);

			(*last_target_R)[0] = VAL(R_TARGET_X);
			(*last_target_R)[1] = VAL(R_TARGET_Y) - 0.9962;
			(*last_target_R)[2] = VAL(R_TARGET_Z);

			LegIK(length, angles_R, limits_R, *last_target_R);
		}
	}

	// // draw the floor
	// setAmbientColor(.1f,.1f,.1f);
	// setDiffuseColor(COLOR_RED);
	// glPushMatrix();
	// glTranslated(-5,0,-5);
	// drawBox(10,0.01f,10);
	// glPopMatrix();

	m_camera->setModelTorso(Vec3f(VAL(XPOS), VAL(YPOS), VAL(ZPOS)));
	// (*metaball_container)[1]->setCenter(Vec3d(VAL(XPOS), 0, 0));
	// metaball_container->render();
	
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		int lod = int(VAL(LOD));
		// Torso
		glPushMatrix();
			glRotated(-90.0, 1.0, 0.0, 0.0);

			drawTorso();

			if (lod > 0)
			{
				drawHead();

				drawArmL(VAL(L_UPPER_ARM_YROT), VAL(L_UPPER_ARM_ZROT), 45.0, 0.0, lod - 1);
				drawArmR(VAL(R_UPPER_ARM_YROT), VAL(R_UPPER_ARM_ZROT), 45.0, 0.0, lod - 1);

				if (VAL(APPLY_IK))
				{
					drawLegL(angles_L[0], angles_L[1], angles_L[2], lod - 1);
					drawLegR(angles_R[0], angles_R[1], angles_R[2], lod - 1);
				}
				else
				{
					drawLegL(VAL(L_THIGH_XROT), VAL(L_THIGH_YROT), VAL(L_LEG_XROT), lod - 1);
					drawLegR(VAL(R_THIGH_XROT), VAL(R_THIGH_YROT), VAL(R_LEG_XROT), lod - 1);
				}

				drawEquipment(VAL(BACK_YROT), VAL(L_EQUIP_YROT), VAL(R_EQUIP_YROT), VAL(L_TURRET_YROT), VAL(R_TURRET_YROT), VAL(L_TURRET_XROT), VAL(R_TURRET_XROT), VAL(TURRET_NUM), lod);
			}

		glPopMatrix();

	glPopMatrix();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];

	// LOD
	controls[LOD] = ModelerControl("Change Level of Detail", 0, 4, 1, 4);
	
	// Light
	controls[LIGHT] = ModelerControl("LIGHT", M_PI / 2, M_PI / 2 + 2 * M_PI, 0.01, M_PI / 2);

	// Whole body
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 2);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);

	// Arm
	controls[L_UPPER_ARM_YROT] = ModelerControl("Left Upper Arm Y Rotation", 10, 135, 0.1f, 10);
	controls[L_UPPER_ARM_ZROT] = ModelerControl("Left Upper Arm Z Rotation", -45, 45, 0.1f, 0);
	controls[R_UPPER_ARM_YROT] = ModelerControl("Right Upper Arm Y Rotation", 10, 135, 0.1f, 10);
	controls[R_UPPER_ARM_ZROT] = ModelerControl("Right Upper Arm Z Rotation", -45, 45, 0.1f, 0);

	// Leg
	controls[L_THIGH_XROT] = ModelerControl("Left Thigh X Rotation", -60, 50, 0.1f, -5);
	controls[R_THIGH_XROT] = ModelerControl("Right Thigh X Rotation", -60, 50, 0.1f, -5);
	controls[L_THIGH_YROT] = ModelerControl("Left Thigh Y Rotation", 0, 90, 0.1f, 0);
	controls[R_THIGH_YROT] = ModelerControl("Right Thigh Y Rotation", 0, 90, 0.1f, 0);
	controls[L_LEG_XROT] = ModelerControl("Left Leg X Rotation", 0, 140, 0.1f, 10);
	controls[R_LEG_XROT] = ModelerControl("Right Leg X Rotation", 0, 140, 0.1f, 10);

	// Equipment
	controls[BACK_YROT] = ModelerControl("Back Equipment Y Rotation", -15, 15, 0.1f, 0);
	controls[L_EQUIP_YROT] = ModelerControl("Left Equipment Y Rotation", -15, 15, 0.1f, 0);
	controls[R_EQUIP_YROT] = ModelerControl("Right Equipment Y Rotation", -15, 15, 0.1f, 0);

	// Turret
	controls[L_TURRET_YROT] = ModelerControl("Left Turret Y Rotation", -30, 225, 1, 0);
	controls[R_TURRET_YROT] = ModelerControl("Right Turret Y Rotation", -30, 225, 1, 0);

	controls[L_TURRET_XROT] = ModelerControl("Left Turret X Rotation", 10, 85, 1, 36);
	controls[R_TURRET_XROT] = ModelerControl("Right Turret X Rotation", 10, 85, 1, 36);

	controls[TURRET_NUM] = ModelerControl("Turret Num", 2, 3, 1, 2); 
	
	// Inverse Kinematics
	controls[L_TARGET_X] = ModelerControl("Left Leg Target X", 0, 0.5, 0.01f, 0);
	controls[R_TARGET_X] = ModelerControl("Right Leg Target X", -0.5, 0, 0.01f, 0);
	controls[L_TARGET_Y] = ModelerControl("Left Leg Target Y", 0, 0.5, 0.01f, 0);
	controls[R_TARGET_Y] = ModelerControl("Right Leg Target Y", 0, 0.5, 0.01f, 0);
	controls[L_TARGET_Z] = ModelerControl("Left Leg Target Z", -0.5, 0, 0.01f, 0);
	controls[R_TARGET_Z] = ModelerControl("Right Leg Target Z", -0.5, 0, 0.01f, 0);

	controls[APPLY_IK] = ModelerControl("Apply IK", 0, 1, 1, 0);

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
