#pragma once

#include <QMainWindow>
#include "ui_TasksWindow.h"

class TasksWindow : public QMainWindow
{
	Q_OBJECT

public:
	TasksWindow(QWidget *parent = nullptr);
	~TasksWindow();

private:
	Ui::TasksWindowClass ui;

	void setTasksWindowSpecifications();
};

