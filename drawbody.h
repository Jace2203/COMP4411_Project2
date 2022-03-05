#ifndef DRAWBODY_H
#define DRAWBODY_H

const double torso_height = 1.2;
const double head_size = 0.36;
const double arm_length = 0.5;
const double leg_length = 0.7;

void drawTorso();

void drawHead();

void drawArmL(double upper_y, double upper_z, double lower_x, double lower_z);
void drawArmR(double upper_y, double upper_z, double lower_x, double lower_z);

void drawLegL();
void drawLegR();

void drawEquipment(double back_y);
void drawBack(double back_y);
void drawEquipmentL();
void drawEquipmentR();

#endif