#include "drawbody.h"

#include "modelerdraw.h"
#include "complexshape.h"

void drawTorso()
{
	glPushMatrix();
		glScaled(1.0, 0.8, 1.0);
		drawCylinder(torso_height, 0.6, 0.5);
        glTranslated(0.0, 0.0, torso_height);
        glScaled(1.0, 1.0, 0.5);
        drawSphere(0.5);
	glPopMatrix();
}

void drawHead()
{
    glPushMatrix();
        glRotated(90.0, 1.0, 0.0, 0.0);
        glTranslated(0.0, head_size + torso_height + 0.24, 0.0);
        drawSphere(head_size);
    glPopMatrix();
}

void drawArmL(double upper_y, double upper_z, double lower_x, double lower_z)
{
    glPushMatrix();
		glTranslated(-0.6, 0.0, torso_height);
		glRotated(180.0, 1.0, 0.0, 0.0);
		glRotated(-upper_y, 0.0, 1.0, 0.0);
		glRotated(upper_z, 0.0, 0.0, 1.0);
        drawSphere(0.11);
		drawCylinder(arm_length, 0.11, 0.1);
				
		glPushMatrix();
		    glTranslated(0.0, 0.0, arm_length);
			glRotated(-lower_x, 1.0, 0.0, 0.0);
            drawSphere(0.1);
			drawCylinder(arm_length, 0.1, 0.09);
		glPopMatrix();

	glPopMatrix();
}

void drawArmR(double upper_y, double upper_z, double lower_x, double lower_z)
{
	glPushMatrix();
		glTranslated(0.6, 0.0, torso_height);
		glRotated(180.0, 1.0, 0.0, 0.0);
		glRotated(upper_y, 0.0, 1.0, 0.0);
		glRotated(upper_z, 0.0, 0.0, 1.0);
        drawSphere(0.11);
		drawCylinder(arm_length, 0.11, 0.1);

		glPushMatrix();
		    glTranslated(0.0, 0.0, arm_length);
            glRotated(-lower_x, 1.0, 0.0, 0.0);
            drawSphere(0.1);
			drawCylinder(arm_length, 0.1, 0.09);
		glPopMatrix();

	glPopMatrix();
}

void drawLegL()
{
    glPushMatrix();
        glTranslated(-0.3, 0.0, 0.0);
        glRotated(180.0, 1.0, 0.0, 0.0);
        drawSphere(0.2);
        drawCylinder(leg_length, 0.2, 0.18);
    glPopMatrix();
}

void drawLegR()
{
    glPushMatrix();
        glTranslated(0.3, 0.0, 0.0);
        glRotated(180.0, 1.0, 0.0, 0.0);
        drawSphere(0.2);
        drawCylinder(leg_length, 0.2, 0.18);
    glPopMatrix();
}

void drawEquipment(double back_y)
{
    glPushMatrix();
        glRotated(90.0, 1.0, 0.0, 0.0);
        glTranslated(0.0, 0.3, -0.55);
        drawBack(back_y);
    glPopMatrix();
}

void drawBack(double back_y)
{
    glPushMatrix();
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

        // Left Equipment
        drawEquipmentL();
        // Right Equipment
        drawEquipmentR();

    glPopMatrix();
}

void drawEquipmentL()
{
    glPushMatrix();
        glTranslated(0.4, 0.0, -0.53);

        glPushMatrix();
            glRotated(-90.0, 1.0, 0.0, 0.0);
            drawCylinder(0.2, 0.1, 0.1);
        glPopMatrix();

        glRotated(-5.0, 0.0, 1.0, 0.0);

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

        glPushMatrix();
            glTranslated(1.35, 0.4, 0.0);
            glPushMatrix();
                glRotated(-90.0, 1.0, 0.0, 0.0);
                drawCylinder(0.4, 0.4, 0.4);
            glPopMatrix();
            
            glTranslated(0.0, 0.4, -0.03);
            glPushMatrix();
                glRotated(180.0, 0.0, 1.0, 0.0);
                glScaled(0.45, 0.45, 0.45);
                drawTurret();
            glPopMatrix();

            glTranslated(0.0, -0.4, 1.4);
            glPushMatrix();
                glRotated(-90.0, 1.0, 0.0, 0.0);
                drawCylinder(0.2, 0.4, 0.4);
            glPopMatrix();

            glTranslated(0.0, 0.2, 0.0);
            glPushMatrix();
                glRotated(180.0, 0.0, 1.0, 0.0);
                glScaled(0.45, 0.45, 0.45);
                drawTurret();
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
}

void drawEquipmentR()
{
    glPushMatrix();
        glTranslated(-0.2, 0.0, -0.53);

        glPushMatrix();
            glRotated(-90.0, 1.0, 0.0, 0.0);
            drawCylinder(0.2, 0.1, 0.1);
        glPopMatrix();

        glRotated(5.0, 0.0, 1.0, 0.0);

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

        glPushMatrix();
            glTranslated(-1.35, 0.4, 0.0);
            glPushMatrix();
                glRotated(-90.0, 1.0, 0.0, 0.0);
                drawCylinder(0.4, 0.4, 0.4);
            glPopMatrix();
            
            glTranslated(0.0, 0.4, -0.03);
            glPushMatrix();
                glRotated(180.0, 0.0, 1.0, 0.0);
                glScaled(0.45, 0.45, 0.45);
                drawTurret();
            glPopMatrix();

            glTranslated(0.0, -0.4, 1.4);
            glPushMatrix();
                glRotated(-90.0, 1.0, 0.0, 0.0);
                drawCylinder(0.2, 0.4, 0.4);
            glPopMatrix();

            glTranslated(0.0, 0.2, 0.0);
            glPushMatrix();
                glRotated(180.0, 0.0, 1.0, 0.0);
                glScaled(0.45, 0.45, 0.45);
                drawTurret();
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
}