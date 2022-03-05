#include "drawbody.h"

#include "modelerdraw.h"
#include "complexshape.h"

void drawTorso()
{
	glPushMatrix();
		glScaled(1.0, 0.8, 1.0);
		drawCylinder(torso_height, 0.5, 0.4);
        glTranslated(0.0, 0.0, torso_height);
        glScaled(1.0, 1.0, 0.5);
        drawSphere(0.4);
	glPopMatrix();
}

void drawHead()
{
    glPushMatrix();
        glRotated(90.0, 1.0, 0.0, 0.0);
        glTranslated(0.0, head_size + torso_height + 0.2, 0.0);
        drawSphere(head_size);
    glPopMatrix();
}

void drawArmL(double upper_y, double upper_z, double lower_x, double lower_z, int lod)
{
    glPushMatrix();
		glTranslated(-0.5, 0.0, torso_height);
		glRotated(180.0, 1.0, 0.0, 0.0);
		glRotated(-upper_y, 0.0, 1.0, 0.0);
		glRotated(upper_z, 0.0, 0.0, 1.0);
        drawSphere(0.11);
		drawCylinder(arm_length, 0.11, 0.1);
		
        if (lod > 1)
        {
            glPushMatrix();
                glTranslated(0.0, 0.0, arm_length);
                glRotated(-lower_x, 1.0, 0.0, 0.0);
                drawSphere(0.1);
                drawCylinder(arm_length, 0.1, 0.09);
            glPopMatrix();
        }

	glPopMatrix();
}

void drawArmR(double upper_y, double upper_z, double lower_x, double lower_z, int lod)
{
	glPushMatrix();
		glTranslated(0.5, 0.0, torso_height);
		glRotated(180.0, 1.0, 0.0, 0.0);
		glRotated(upper_y, 0.0, 1.0, 0.0);
		glRotated(upper_z, 0.0, 0.0, 1.0);
        drawSphere(0.11);
		drawCylinder(arm_length, 0.11, 0.1);

        if (lod > 1)
        {
            glPushMatrix();
                glTranslated(0.0, 0.0, arm_length);
                glRotated(-lower_x, 1.0, 0.0, 0.0);
                drawSphere(0.1);
                drawCylinder(arm_length, 0.1, 0.09);
            glPopMatrix();
        }

	glPopMatrix();
}

void drawLegL(double leg_x)
{
    glPushMatrix();
        glTranslated(-0.3, 0.0, 0.0);
        glRotated(180.0 + leg_x, 1.0, 0.0, 0.0);
        drawSphere(0.15);
        drawCylinder(leg_length, 0.15, 0.12);
    glPopMatrix();
}

void drawLegR(double leg_x)
{
    glPushMatrix();
        glTranslated(0.3, 0.0, 0.0);
        glRotated(180.0 + leg_x, 1.0, 0.0, 0.0);
        drawSphere(0.15);
        drawCylinder(leg_length, 0.15, 0.12);
    glPopMatrix();
}

void drawEquipment(double back_y, double l_equip_y, double r_equip_y, double l_turret_y, double r_turret_y, double l_turret_x, double r_turret_x, int lod)
{
    glPushMatrix();
        glRotated(90.0, 1.0, 0.0, 0.0);
        glTranslated(0.0, 0.3, -0.45);
        // glScaled(0.8, 0.8, 0.8);

        // parts behind the back
        drawSphere(0.1);
        glRotated(back_y, 0.0, 1.0, 0.0);
        glTranslated(-0.1, -0.1, -0.1);
        drawBox(0.2, 0.2, -0.2);

        glPushMatrix();
            glTranslated(0.0, 0.0, -0.2);
            glPushMatrix();
                glRotated(50.0, 1.0, 0.0, 0.0);
                drawBox(0.2, 0.2, -0.5);
            glPopMatrix();

            glPushMatrix();
                glTranslated(-0.1, -0.1, -0.18);
                drawBox(0.4, 0.7, -0.3);
            glPopMatrix();
        glPopMatrix();

        if (lod > 0)
        {
            // Left Equipment
            drawEquipmentL(l_equip_y, l_turret_y, l_turret_x, lod - 1);
            // Right Equipment
            drawEquipmentR(r_equip_y, r_turret_y, r_turret_x, lod - 1);
        }

    glPopMatrix();
}

void drawEquipmentL(double equip_y, double turret_y, double turret_x, int lod)
{
    glPushMatrix();
        glTranslated(0.4, 0.0, -0.53);


        if (lod > 0)
        {
            glPushMatrix();
                glRotated(-90.0, 1.0, 0.0, 0.0);
                drawCylinder(0.2, 0.1, 0.1);
            glPopMatrix();

            glRotated(-equip_y, 0.0, 1.0, 0.0);

            glPushMatrix();
                glRotated(-90.0, 1.0, 0.0, 0.0);
                glTranslated(1.0, 0.0, 0.0);
                drawCylinder(0.2, 0.2, 0.2);
            glPopMatrix();

            glTranslated(0.0, 0.0, 0.1);
            drawBox(1.0, 0.2, -0.2);

            glPushMatrix();
                glRotated(180.0, 0.0, 1.0, 0.0);
                glTranslated(-2.1, -0.3, 0.5);
                glScaled(0.75, 0.75, 0.75);
                drawShip();
            glPopMatrix();

            drawTurrets(LEFT, turret_y, turret_x, lod - 1);
        }

    glPopMatrix();
}

void drawEquipmentR(double equip_y, double turret_y, double turret_x, int lod)
{
    glPushMatrix();
        glTranslated(-0.2, 0.0, -0.53);

        if (lod > 0)
        {
            glPushMatrix();
                glRotated(-90.0, 1.0, 0.0, 0.0);
                drawCylinder(0.2, 0.1, 0.1);
            glPopMatrix();

            glRotated(equip_y, 0.0, 1.0, 0.0);

            glPushMatrix();
                glRotated(-90.0, 1.0, 0.0, 0.0);
                glTranslated(-1.0, 0.0, 0.0);
                drawCylinder(0.2, 0.2, 0.2);
            glPopMatrix();

            glTranslated(0.0, 0.0, 0.1);
            drawBox(-1.0, 0.2, -0.2);

            glPushMatrix();
                glRotated(180.0, 0.0, 1.0, 0.0);
                glTranslated(0.59, -0.3, 0.5);
                glScaled(0.75, 0.75, 0.75);
                drawShip();
            glPopMatrix();

            drawTurrets(RIGHT, turret_y, turret_x, lod - 1);
        }

    glPopMatrix();
}

void drawCompleteTurret(double turret_y, double turret_x, int lod)
{
    glPushMatrix();
        glRotated(turret_y, 0.0, 1.0, 0.0);
        drawTurret();
        
        glTranslated(0.0, 0.1, -1.1);
        glRotated(-(180 - turret_x), 1.0, 0.0, 0.0);

        if (lod > 0)
        {
            glPushMatrix();
                glTranslated(-0.275, 0.0, 0.0);
                drawCylinder(2.1, 0.1, 0.1);
            glPopMatrix();
            
            glPushMatrix();
                glTranslated(0.275, 0.0, 0.0);
                drawCylinder(2.1, 0.1, 0.1);
            glPopMatrix();
        }
    glPopMatrix();
}

void drawTurrets(int dir, double turret_y, double turret_x, int lod)
{
    glPushMatrix();
        glTranslated(dir * 1.35, 0.4, 0.0);
        glPushMatrix();
            glRotated(-90.0, 1.0, 0.0, 0.0);
            drawCylinder(0.4, 0.4, 0.4);
        glPopMatrix();

        glTranslated(0.0, 0.4, -0.03);
        if (lod > 0)
        {
            glPushMatrix();
                glRotated(180.0, 0.0, 1.0, 0.0);
                glScaled(0.45, 0.45, 0.45);
                drawCompleteTurret(double(dir) * turret_y, turret_x, lod - 1);
            glPopMatrix();
        }

        glTranslated(0.0, -0.4, 1.4);
        glPushMatrix();
            glRotated(-90.0, 1.0, 0.0, 0.0);
            drawCylinder(0.2, 0.4, 0.4);
        glPopMatrix();

        if (lod > 0)
        {
            glTranslated(0.0, 0.2, 0.0);
            glPushMatrix();
                glRotated(180.0, 0.0, 1.0, 0.0);
                glScaled(0.45, 0.45, 0.45);
                drawCompleteTurret(double(dir) * turret_y, turret_x, lod - 1);
            glPopMatrix();
        }
    glPopMatrix();
}