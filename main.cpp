/*A1 CAR RACER GAME

Created By:
	Pratyakshya Bhakuni     -     101903140
	Mridul Sahi             -     101903128 */
#include<GL/glut.h>
#include<iostream>//for strlen
#include<stdlib.h>
int i, q;
int score = 0;//for score counting
int screen = 0;
bool collide = false;//check if car collide to make game over
char buffer[10];
int vehicleX = 200, vehicleY = 70;
int ovehicleX[4], ovehicleY[4];
int divx = 250, divy = 4, movd;
void drawText(char ch[], int xpos, int ypos)//draw the text for score and game over
{
	int numofchar = strlen(ch);
	glLoadIdentity();
	glRasterPos2f(xpos, ypos);
	for (i = 0; i <= numofchar - 1; i++)
	{

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);//font used here, may use other font also
	}
}


void drawTextNum(char ch[], int numtext, int xpos, int ypos)//counting the score
{
	int len;
	int k;
	k = 0;
	len = numtext - strlen(ch);
	glLoadIdentity();
	glRasterPos2f(xpos, ypos);
	for (i = 0; i <= numtext - 1; i++)
	{
		if (i < len)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0');
		else
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
			k++;
		}

	}
}


void ovpos()
{
	glClearColor(0.6549, 0.7450, 0.8274, 1);
	for (i = 0; i < 4; i++)
	{
		if (rand() % 2 == 0)
		{
			ovehicleX[i] = 200;
		}
		else
		{
			ovehicleX[i] = 300;
		}
		ovehicleY[i] = 1000 - i * 160;
	}
}


void drawRoad()
{
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(250 - 100, 500);
	glVertex2f(250 - 100, 0);
	glVertex2f(250 + 100, 0);
	glVertex2f(250 + 100, 500);
	glEnd();
}


void drawDivider()//white patch drawn in middle of road
{
	glLoadIdentity();
	glTranslatef(0, movd, 0);
	for (i = 1; i <= 10; i++)
	{
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glVertex2f(divx - 5, divy * 15 * i + 18);
		glVertex2f(divx - 5, divy * 15 * i - 18);
		glVertex2f(divx + 5, divy * 15 * i - 18);
		glVertex2f(divx + 5, divy * 15 * i + 18);
		glEnd();
	}
	glLoadIdentity();
}


void drawVehicle()//car for racing
{
	glPointSize(10.0);
	glBegin(GL_POINTS);//tire
	glColor3f(0, 0, 0);
	glVertex2f(vehicleX - 25, vehicleY + 16);
	glVertex2f(vehicleX + 25, vehicleY + 16);
	glVertex2f(vehicleX - 25, vehicleY - 16);
	glVertex2f(vehicleX + 25, vehicleY - 16);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(255, 240, 0);//middle body
	glVertex2f(vehicleX - 25, vehicleY + 20);
	glVertex2f(vehicleX - 25, vehicleY - 20);
	glVertex2f(vehicleX + 25, vehicleY - 20);
	glVertex2f(vehicleX + 25, vehicleY + 20);
	glEnd();

	glBegin(GL_QUADS);//up body
	glColor3f(0.2235, 0.294, 0.62);
	glVertex2f(vehicleX - 23, vehicleY + 20);
	glVertex2f(vehicleX - 19, vehicleY + 40);
	glVertex2f(vehicleX + 19, vehicleY + 40);
	glVertex2f(vehicleX + 23, vehicleY + 20);
	glEnd();

	glBegin(GL_QUADS);//down body
	glColor3f(0.2235, 0.294, 0.62);
	glVertex2f(vehicleX - 23, vehicleY - 20);
	glVertex2f(vehicleX - 19, vehicleY - 35);
	glVertex2f(vehicleX + 19, vehicleY - 35);
	glVertex2f(vehicleX + 23, vehicleY - 20);
	glEnd();
}

void drawOVehicle()//other cars
{

	for (i = 0; i < 4; i++)
	{
		glPointSize(10.0);
		glBegin(GL_POINTS);//tire
		glColor3f(0, 0, 0);
		glVertex2f(ovehicleX[i] - 25, ovehicleY[i] + 16);
		glVertex2f(ovehicleX[i] + 25, ovehicleY[i] + 16);
		glVertex2f(ovehicleX[i] - 25, ovehicleY[i] - 16);
		glVertex2f(ovehicleX[i] + 25, ovehicleY[i] - 16);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.8, 0.2, 0.8);//middle body
		glVertex2f(ovehicleX[i] - 25, ovehicleY[i] + 20);
		glVertex2f(ovehicleX[i] - 25, ovehicleY[i] - 20);
		glVertex2f(ovehicleX[i] + 25, ovehicleY[i] - 20);
		glVertex2f(ovehicleX[i] + 25, ovehicleY[i] + 20);
		glEnd();

		glBegin(GL_QUADS);//up body
		glColor3f(0.4, 0.3, 0.6);
		glVertex2f(ovehicleX[i] - 23, ovehicleY[i] + 20);
		glVertex2f(ovehicleX[i] - 19, ovehicleY[i] + 40);
		glVertex2f(ovehicleX[i] + 19, ovehicleY[i] + 40);
		glVertex2f(ovehicleX[i] + 23, ovehicleY[i] + 20);
		glEnd();

		glBegin(GL_QUADS);//down body
		glColor3f(0.4, 0.3, 0.6);
		glVertex2f(ovehicleX[i] - 23, ovehicleY[i] - 20);
		glVertex2f(ovehicleX[i] - 19, ovehicleY[i] - 35);
		glVertex2f(ovehicleX[i] + 19, ovehicleY[i] - 35);
		glVertex2f(ovehicleX[i] + 23, ovehicleY[i] - 20);
		glEnd();

		ovehicleY[i] = ovehicleY[i] - 8;

		if (ovehicleY[i] > vehicleY - 25 - 25 && ovehicleY[i] < vehicleY + 25 + 25 && ovehicleX[i] == vehicleX)
		{
			collide = true;
		}

		if (ovehicleY[i] < -25)
		{
			if (rand() % 2 == 0)
			{
				ovehicleX[i] = 200;
			}
			else
			{
				ovehicleX[i] = 300;
			}
			ovehicleY[i] = 600;
		}
	}
}

void Specialkey(int key, int x, int y)//allow to use navigation key for movement of car
{
	switch (key)
	{
	case GLUT_KEY_UP:
		for (i = 0; i < 4; i++)
		{
			ovehicleY[i] = ovehicleY[i] - 10;
		}
		movd = movd - 20;
		break;
	case GLUT_KEY_DOWN:
		for (i = 0; i < 4; i++)
		{
			ovehicleY[i] = ovehicleY[i] + 10;
		}
		movd = movd + 20;
		break;
	case GLUT_KEY_LEFT:vehicleX = 200;
		break;
	case GLUT_KEY_RIGHT:vehicleX = 300;
		break;

	}

	glutPostRedisplay();
}

void Normalkey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':if (screen == 0)
		screen = 1;
		break;
	case '2':if (screen == 1)
		screen = 2;
		break;
	case 27:exit(0);
	}
}


void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}


void display()
{
	if (screen == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1,1,1);
		drawText((char*)"WELCOME", 170, 290);
		drawText((char*)"PLAYER", 170, 250);
		drawText((char*)"Press 1 to continue", 170, 150);
		drawText((char*)"Created By:      Pratyakshya Bhakuni, Mridul Sahi", 170, 110);
		glutSwapBuffers();
	}
	else if (screen == 1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1, 1, 1);
		drawText((char*)"Use up key to accelerate", 170, 290);
		drawText((char*)"Use left key to move left", 170, 250);
		drawText((char*)"Use right key to move right", 170, 210);
		drawText((char*)"Use down key to decelerate", 170, 170);
		drawText((char*)"Press 2 to continue", 170, 130);
		glutSwapBuffers();
	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT);
		drawRoad();
		drawDivider();
		drawVehicle();
		drawOVehicle();
		movd = movd - 16;
		if (movd < -60)
		{
			movd = 0;
		}

		score = score + 1;
		glColor3f(1, 1, 1);
		drawText((char*)"Score:", 360, 455);
		_itoa_s(score, buffer, 10);
		drawTextNum(buffer, 6, 420, 455);
		glutSwapBuffers();
		for (q = 0; q <= 10000000; q++) { ; }
		if (collide == true)
		{
			glColor3f(0, 0, 0);
			drawText((char*)"Game Over", 200, 250);
			glutSwapBuffers();
			getchar();
			exit(0);
		}
	}
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 500);
	glutCreateWindow("A1 Racer Car game");
	ovpos();
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(Specialkey);
	glutKeyboardFunc(Normalkey);
	glutIdleFunc(display);
	glutMainLoop();
}
