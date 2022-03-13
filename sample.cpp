// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"
#include "complexshape.h"
#include "drawbody.h"

#include "cmath"

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

double ani_height = -(head_size + torso_height)/3,
	   cur_height = 0,
	   chg_height = 0,
	   ani_theta = acos(-ani_height)*180/M_PI,
	   cur_theta = 0,
	   chg_theta = 0,
	   ani_angle  = 15,
	   cur_angle  = ani_angle,
	   chg_angle  = 0,
	   ani_wave   = 45,
	   cur_wave   = ani_wave,
	   chg_wave   = 0,
	   time_wave  = 3;

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

	if (ModelerApplication::Instance()->IsAnimating())
	{
		if (cur_height <= ani_height)
			chg_height = -ani_height /15;
		else if (cur_height >= 0)
			chg_height = ani_height /15;

		if (cur_angle >= ani_angle)
			chg_angle = -ani_angle /15;
		else if (cur_angle <= -ani_angle)
			chg_angle = ani_angle /15;

		if (cur_wave >= ani_wave)
			chg_wave = -ani_wave * time_wave /15;
		else if (cur_wave <= -ani_wave)
			chg_wave = ani_wave * time_wave /15;

		if (cur_theta >= ani_theta)
			chg_theta = -ani_theta /15;
		else if (cur_theta <= 0)
			chg_theta = ani_theta /15;

		cur_height += chg_height;
		cur_angle += chg_angle;
		cur_wave += chg_wave;
		cur_theta += chg_theta;
	}

	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS)+cur_height, VAL(ZPOS));

	if (ModelerApplication::Instance()->IsAnimating())
		glRotated(cur_angle, 0, 1, 0);

		int lod = int(VAL(LOD));
		// Torso
		glPushMatrix();
			glRotated(-90.0, 1.0, 0.0, 0.0);

			drawTorso();

			if (lod > 0)
			{
				drawHead();

				double LZ = (ModelerApplication::Instance()->IsAnimating()) ? cur_wave : VAL(L_UPPER_ARM_ZROT),
					   RZ = (ModelerApplication::Instance()->IsAnimating()) ? cur_wave : VAL(R_UPPER_ARM_ZROT);

				drawArmL(VAL(L_UPPER_ARM_YROT), LZ, 45.0, 0.0, lod - 1);
				drawArmR(VAL(R_UPPER_ARM_YROT), RZ, 45.0, 0.0, lod - 1);

				//glTranslated(0, 0, -cur_height);

				double LTX = (ModelerApplication::Instance()->IsAnimating()) ? -cur_theta : VAL(L_THIGH_XROT),
					   RTX = (ModelerApplication::Instance()->IsAnimating()) ? -cur_theta : VAL(R_THIGH_XROT),
					   LLX = (ModelerApplication::Instance()->IsAnimating()) ? 2*cur_theta : VAL(L_LEG_XROT),
					   RLX = (ModelerApplication::Instance()->IsAnimating()) ? 2*cur_theta : VAL(R_LEG_XROT);

				drawLegL(LTX, VAL(L_THIGH_YROT), LLX);
				drawLegR(RTX, VAL(R_THIGH_YROT), RLX);

				//glTranslated(0, 0, cur_height);

				drawEquipment(VAL(BACK_YROT), VAL(L_EQUIP_YROT), VAL(R_EQUIP_YROT), VAL(L_TURRET_YROT), VAL(R_TURRET_YROT), VAL(L_TURRET_XROT), VAL(R_TURRET_XROT), lod);
			}

		glPopMatrix();

	glPopMatrix();

	// drawTurret();
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
	controls[L_THIGH_XROT] = ModelerControl("Left Thigh X Rotation", -60, 50, 0.1f, 0);
	controls[R_THIGH_XROT] = ModelerControl("Right Thigh X Rotation", -60, 50, 0.1f, 0);
	controls[L_THIGH_YROT] = ModelerControl("Left Thigh Y Rotation", 0, 90, 0.1f, 0);
	controls[R_THIGH_YROT] = ModelerControl("Right Thigh Y Rotation", 0, 90, 0.1f, 0);
	controls[L_LEG_XROT] = ModelerControl("Left Leg X Rotation", 0, 140, 0.1f, 0);
	controls[R_LEG_XROT] = ModelerControl("Right Leg X Rotation", 0, 140, 0.1f, 0);

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

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
