#include "stdafx.h"
#include "cpp_phys_sim_demo.h"

cpp_phys_sim_demo::cpp_phys_sim_demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.btnRun, SIGNAL(clicked()), SLOT(btnRunClick()));
	connect(ui.btnUpdate, SIGNAL(clicked()), SLOT(btnUpdateClick()));
	connect(this, SIGNAL(close()), SLOT(processClose()));
}

cpp_phys_sim_demo::~cpp_phys_sim_demo()
{}

void cpp_phys_sim_demo::btnRunClick()
{
	float mass = 0.0f;
	float height = 0.0f;
	float gravity = 0.0f;
	float bounce = 0.0f;

	mass = ui.edMass->text().toFloat();
	height = ui.edHeight->text().toFloat();
	gravity = ui.edGrav->text().toFloat();
	bounce = ui.edBounce->text().toFloat();

	simEnt->setupSim(mass,height,gravity,bounce);
}

void cpp_phys_sim_demo::btnUpdateClick()
{
	QString txt;
	txt.setNum(simEnt->getX());
	ui.labelX->setText("X = "+txt);
	txt.setNum(simEnt->getY());
	ui.labelY->setText("Y = "+txt);
	txt.setNum(simEnt->getIterations());
	ui.labelI->setText("I = " + txt);
}


void cpp_phys_sim_demo::setSimEnt(simulated_enity * se)
{
	simEnt = se;
}

void cpp_phys_sim_demo::processClose()
{
	simEnt->setNeedClose(true);
}