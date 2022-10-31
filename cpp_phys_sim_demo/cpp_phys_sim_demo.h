#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_cpp_phys_sim_demo.h"

class cpp_phys_sim_demo : public QMainWindow
{
    Q_OBJECT

public:
    cpp_phys_sim_demo(QWidget *parent = nullptr);
    ~cpp_phys_sim_demo();
	void setSimEnt(simulated_enity * se);

private:
    Ui::cpp_phys_sim_demoClass ui;
	simulated_enity * simEnt;

private slots:
	void btnRunClick();
	void btnUpdateClick();
};
