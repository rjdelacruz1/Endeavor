#pragma once

#include <QMainWindow>
#include "ui_TasksWindow.h"
#include "TaskFile.h"
#include "Task.h"
#include <QLabel>
#include <QListWidgetItem>
#include <QVector>
#include <QObject>
#include <QCloseEvent>

class TasksWindow : public QMainWindow
{
	Q_OBJECT

public:
	TasksWindow(QWidget *parent = nullptr);
	~TasksWindow();

private:
	Ui::TasksWindowClass ui;
	TaskFile taskFile;
	QString taskPath;
	QListWidgetItem *itemBeingEdited = nullptr;
	//QString taskPath = taskFile.taskFilePath();

	void setTasksWindowSpecifications();
	void setUpConnections();
	void addTaskEntry();
	void moveTaskItem(QListWidget* from, QListWidget* to, QListWidgetItem* item);
	void populateLists(const QVector<Task>& v);
	void handleListSelection();
	void enterEditMode(QListWidgetItem* item);
	void confirmEdit();
	void exitEditMode();
	void syncTasksFromList();
	void closeEvent(QCloseEvent* event);
};

