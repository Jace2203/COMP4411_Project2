#include "drawbody.h"

#include "modelerdraw.h"
#include "complexshape.h"
#include "metaball.h"

#include "vec.h"
#include "bitmap.h"
#include <cstring>

bmp::bmp():width(0), height(0), data(nullptr) {}

bmp::bmp(char* in)
{
    data = readBMP(in, width, height);
}

bmp* BMP = new bmp[NUM];

void drawTorso()
{
	glPushMatrix();
		glScaled(1.0, 0.8, 1.0);
        loadTexture(BODY);
        glEnable(GL_TEXTURE_2D);
		drawCylinder(torso_height, 0.5, 0.4);
        glTranslated(0.0, 0.0, torso_height);
        glScaled(1.0, 1.0, 0.5);
        loadTexture(BODY);
        drawSphere(0.4);
        glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    glPushMatrix();
        glTranslated(0.175, -0.25, 1.05);
        drawSphere(0.2);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-0.175, -0.25, 1.05);
        drawSphere(0.2);
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

void drawArmL(double upper_y, double upper_z, double lower_x, double lower_z, MetaballContainer* hand, int lod)
{
    glPushMatrix();
		glTranslated(-0.5, 0.0, torso_height);
		glRotated(180.0, 1.0, 0.0, 0.0);
		glRotated(-upper_y, 0.0, 1.0, 0.0);
		glRotated(upper_z, 0.0, 0.0, 1.0);
        loadTexture(BLACK);
        glEnable(GL_TEXTURE_2D);
        drawSphere(0.11);
        loadTexture(HAND_LEFT);
		drawCylinder(arm_length, 0.11, 0.1);
		
        if (lod > 1)
        {
            glPushMatrix();
                glTranslated(0.0, 0.0, arm_length);
                glRotated(-lower_x, 1.0, 0.0, 0.0);
                loadTexture(BLACK);
                drawSphere(0.1);
                loadTexture(BLACK);
                drawCylinder(arm_length, 0.1, 0.09);
                glTranslated(-0.025, 0.0, arm_length + 0.1);
                glDisable(GL_TEXTURE_2D);
                setDiffuseColor(230/255, 208/255, 195/255);
                hand->render();
                setDiffuseColor(1, 1, 1);
            glPopMatrix();
        }

	glPopMatrix();
}

void drawArmR(double upper_y, double upper_z, double lower_x, double lower_z, MetaballContainer* hand, int lod)
{
	glPushMatrix();
		glTranslated(0.5, 0.0, torso_height);
		glRotated(180.0, 1.0, 0.0, 0.0);
		glRotated(upper_y, 0.0, 1.0, 0.0);
		glRotated(upper_z, 0.0, 0.0, 1.0);
        loadTexture(BLACK);
        glEnable(GL_TEXTURE_2D);
        drawSphere(0.11);
        loadTexture(HAND_RIGHT);
		drawCylinder(arm_length, 0.11, 0.1);

        if (lod > 1)
        {
            glPushMatrix();
                glTranslated(0.0, 0.0, arm_length);
                glRotated(-lower_x, 1.0, 0.0, 0.0);
                loadTexture(BLACK);
                drawSphere(0.1);
                loadTexture(BLACK);
                drawCylinder(arm_length, 0.1, 0.09);
                glTranslated(-0.025, 0.0, arm_length + 0.1);
                glDisable(GL_TEXTURE_2D);
                setDiffuseColor(230/366, 208/255, 195/255);
                hand->render();
                setDiffuseColor(1, 1, 1);
            glPopMatrix();
        }

	glPopMatrix();
}

void drawLegL(double thigh_x, double thigh_y, double leg_x, int lod)
{
    glPushMatrix();
        glTranslated(0.3, 0.0, 0.0);
        glRotated(thigh_y, 0.0, 0.0, 1.0);
        glRotated(180.0 + thigh_x, 1.0, 0.0, 0.0);
        glEnable(GL_TEXTURE_2D);
        loadTexture(PINK);
        drawSphere(0.15);
        loadTexture(LEG_TOP);
        drawCylinder(leg_length, 0.15, 0.12);
        glTranslated(0.0, 0.0, leg_length);
        loadTexture(LEG_DOWN);
        drawSphere(0.12);

        if (lod)
        {
            glPushMatrix();
                glRotated(leg_x, 1.0, 0.0, 0.0);
                loadTexture(LEG_DOWN);
                drawCylinder(leg_length, 0.12, 0.11);
            glPopMatrix();
        }

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void drawLegR(double thigh_x, double thigh_y, double leg_x, int lod)
{
    glPushMatrix();
        glTranslated(-0.3, 0.0, 0.0);
        glRotated(thigh_y, 0.0, 0.0, -1.0);
        glRotated(180.0 + thigh_x, 1.0, 0.0, 0.0);
        glEnable(GL_TEXTURE_2D);
        loadTexture(PINK);
        drawSphere(0.15);
        loadTexture(LEG_TOP);
        drawCylinder(leg_length, 0.15, 0.12);
        glTranslated(0.0, 0.0, leg_length);
        loadTexture(LEG_DOWN);
        drawSphere(0.12);

        if (lod)
        {
            glPushMatrix();
                glRotated(leg_x, 1.0, 0.0, 0.0);
                loadTexture(LEG_DOWN);
                drawCylinder(leg_length, 0.12, 0.11);
            glPopMatrix(); 
        }

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void drawEquipment(double back_y, double l_equip_y, double r_equip_y, double l_turret_y, double r_turret_y, double l_turret_x, double r_turret_x, int turret_num, int lod)
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
            drawEquipmentL(l_equip_y, l_turret_y, l_turret_x, turret_num, lod - 1);
            // Right Equipment
            drawEquipmentR(r_equip_y, r_turret_y, r_turret_x, turret_num, lod - 1);
        }

    glPopMatrix();
}

void drawEquipmentL(double equip_y, double turret_y, double turret_x, int turret_num, int lod)
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

            drawTurrets(LEFT, turret_y, turret_x, turret_num, lod - 1);
        }

    glPopMatrix();
}

void drawEquipmentR(double equip_y, double turret_y, double turret_x, int turret_num, int lod)
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

            drawTurrets(RIGHT, turret_y, turret_x, turret_num, lod - 1);
        }

    glPopMatrix();
}

void drawCompleteTurret(double turret_y, double turret_x, int turret_num, int lod)
{
    glPushMatrix();
        glRotated(turret_y, 0.0, 1.0, 0.0);
        if (turret_num == 2)
        {
            drawTurret2();
            
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
        }
        else
        {
            drawTurret3();

            glTranslated(0.0, 0.1, -1.2);
            glRotated(-(180 - turret_x), 1.0, 0.0, 0.0);
            if (lod > 0)
            {
                drawCylinder(2.3, 0.14, 0.14);
                
                glPushMatrix();
                    glTranslated(0.5, 0.0, 0.0);
                    drawCylinder(2.3, 0.14, 0.14);
                glPopMatrix();

                glPushMatrix();
                    glTranslated(-0.5, 0.0, 0.0);
                    drawCylinder(2.3, 0.14, 0.14);
                glPopMatrix();
            }
        }
    glPopMatrix();
}

void drawTurrets(int dir, double turret_y, double turret_x, int turret_num, int lod)
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
                drawCompleteTurret(double(dir) * turret_y, turret_x, turret_num, lod - 1);
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
                drawCompleteTurret(double(dir) * turret_y, turret_x, turret_num, lod - 1);
            glPopMatrix();
        }
    glPopMatrix();
}

void drawHair()
{
    double hairLength = 0.4 + head_size, theta;
    double size = 0.4;

    glPushMatrix();

        glRotated(90.0, 1.0, 0.0, 0.0);
        glTranslated(0.0, head_size + torso_height + 0.2, 0.0);
        //drawSphere(head_size);

        for(int i = 220; i < 320; ++i)
        {
            glBegin(GL_POLYGON);
                glVertex3d(size*cos(i*M_PI/180), 0, size*sin(i*M_PI/180));
                glVertex3d(size*cos((i)*M_PI/180), -hairLength, size*sin((i)*M_PI/180));
                glVertex3d(size*cos((i+1)*M_PI/180), -hairLength, size*sin((i+1)*M_PI/180));
                glVertex3d(size*cos((i+1)*M_PI/180), 0, size*sin((i+1)*M_PI/180));
            glEnd();
        }

    glPopMatrix();
}

void initTexture()
{
    char image[][30] = {
        "black.bmp",
        "pink.bmp",
        "leg_top.bmp",
        "leg_down.bmp",
        "body2.bmp",
        "hand_left.bmp",
        "hand_right.bmp"
    };

    for(int i = 0; i < NUM; ++i)
        BMP[i] = bmp(image[i]);
}

void loadTexture(int index)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP[index].width, BMP[index].height, 0, GL_RGB, GL_UNSIGNED_BYTE, BMP[index].data );
}

void drawLsystem(double IT, double DV, double IA, double AOI, double BY)
{
    char axiom[65536*6] = "X";
    for(int i = 0; i < IT; ++i)
    {
        char temp[65536*6] = "";
        for(int j = 0; axiom[j] != '\0'; ++j)
        {
            switch (axiom[j])
            {
                case 'X':
                    strcat(temp, "F[+X]F[+X]-X");
                    break;
                case 'F':
                    strcat(temp, "FF");
                    break;
                default:
                    strncat(temp, axiom+j, 1);
                    break;
            }
        }
        strcpy(axiom, temp);
    }

    glPushMatrix();
    glRotated(-BY, 0, 1, 0);
    glTranslated(0, 1.55, 1.30);
    glRotated(45, 1, 0, 0);

    glScaled(DV, DV, DV);
    glRotated(IA, 0, 0, 1);
    for(int j = 0; axiom[j] != '\0'; ++j)
    {
        switch (axiom[j])
        {
            case 'F':
                glBegin(GL_LINE_STRIP);
                    glVertex3d(0, 0, 0);
                    glVertex3d(1, 0, 0);
                glEnd();
                glTranslated(1, 0, 0);
                break;
            case '[':
                glPushMatrix();
                break;
            case '-':
                glRotated(AOI, 0, 0, 1);
                break;
            case ']':
                glPopMatrix();
                break;
            case '+':
                glRotated(-AOI, 0, 0, 1);
                break;
        }
    }
    glPopMatrix();
}