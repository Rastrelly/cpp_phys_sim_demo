#include "stdafx.h"
#include "cpp_phys_sim_demo.h"
#include <QtWidgets/QApplication>
#include  <thread>
#include <atomic>
#include <GL/freeglut.h>



simulated_enity simEnt;
float wl, wr, wb, wt;
std::atomic<bool> glutRefr = false;

void simThreadFunc(simulated_enity * se);
void glutThreadFunc(simulated_enity * se, int argc, char *argv[]);

void initGLUT(int argc, char *argv[]);
void cbIdle();
void cbDisplay();

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	cpp_phys_sim_demo w;
	w.show();		
	
	std::thread simThread(simThreadFunc, &simEnt);
	std::thread glutThread(glutThreadFunc, &simEnt, argc, argv);

	w.setSimEnt(&simEnt);	

	return a.exec();

	simThread.join();
	glutThread.join();
}

void simThreadFunc(simulated_enity * se)
{
	while (true)
	{
		simEnt.runSimActions();
	}
}

void glutThreadFunc(simulated_enity * se, int argc, char *argv[])
{
	initGLUT(argc,argv);
}

void initGLUT(int argc, char *argv[])
{
	glutInit(&argc, argv); //initializing GLUT

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(640, 480);

	glutCreateWindow("SIM DISPLAY");

	//OpenGL setup block
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

	//GLUT launch block
	glutIdleFunc(cbIdle);
	glutDisplayFunc(cbDisplay);

	//setup simulated entity
	simEnt.setNeedRefresh(true);

	glutMainLoop();
}

void cbIdle()
{
	if (simEnt.getNeedRefresh())
	{
		simEnt.setNeedRefresh(false);
		glutRefr = true;
	}
	cbDisplay();
}

void cbDisplay()
{
	if (glutRefr)
	{
		glutRefr = false;

		float sh = 1.1f*(simEnt.getHeight());
		float sw = (sh / 480.0f)*640.0f;

		wl = -sw / 2.0f;
		wr = sw / 2.0f;
		wb = -sh * 0.1f;
		wt = sh * 0.9f;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(wl, wr, wb, wt);

		//draw scene
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//draw ground
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);

		glVertex2f(-wl / 2, 0.0f);
		glVertex2f(wl / 2, 0.0f);

		glEnd();

		//draw entity
		float entSize = 2.5f;

		glBegin(GL_LINE_LOOP);
		glColor3f(1.0f, 0.0f, 0.0f);

		glVertex2f(simEnt.getX() - entSize, simEnt.getY() - entSize);
		glVertex2f(simEnt.getX() - entSize, simEnt.getY() + entSize);
		glVertex2f(simEnt.getX() + entSize, simEnt.getY() + entSize);
		glVertex2f(simEnt.getX() + entSize, simEnt.getY() - entSize);

		glEnd();

		glutSwapBuffers();
	}
}

