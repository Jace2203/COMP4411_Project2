#ifndef _MODELER_GLOBALS_H
#define _MODELER_GLOBALS_H

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif

// This is a list of the controls for the SampleModel
// We'll use these constants to access the values 
// of the controls from the user interface.
enum SampleModelControls
{
	LOD,
	DLS, DV, IA, AOI, IT,
	XPOS, YPOS, ZPOS,
	L_UPPER_ARM_YROT, R_UPPER_ARM_YROT,
	L_UPPER_ARM_ZROT, R_UPPER_ARM_ZROT,
	L_LEG_XROT, R_LEG_XROT,
	BACK_YROT,
	L_EQUIP_YROT, R_EQUIP_YROT,
	L_TURRET_YROT, R_TURRET_YROT,
	L_TURRET_XROT, R_TURRET_XROT,
	NUMCONTROLS
};

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))

#endif