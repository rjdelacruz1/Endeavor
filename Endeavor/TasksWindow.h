#pragma once

#include <QMainWindow>
#include "ui_TasksWindow.h"
#include "QLabel"
#include "QListWidgetItem"

class TasksWindow : public QMainWindow
{
	Q_OBJECT

public:
	TasksWindow(QWidget *parent = nullptr);
	~TasksWindow();

private:
	Ui::TasksWindowClass ui;

	void setTasksWindowSpecifications();
	void addTaskEntry();
	void moveTaskItem(QListWidget* from, QListWidget* to, QListWidgetItem* item);
};

