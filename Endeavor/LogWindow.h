#pragma once

#include <QWidget>
#include "ui_LogWindow.h"
#include "Log.h"
#include "LogFile.h"
#include <QLabel>
#include <QListWidgetItem>
#include <QVector>


class LogWindow : public QWidget
{
	Q_OBJECT

public:
	LogWindow(QWidget *parent = nullptr);
	~LogWindow();

private:
	Ui::LogWindowClass ui;

	LogFile logFile;
	QString logPath;
	QListWidgetItem* itemBeingEdited = nullptr;

	void setLogWindowSpecifications();
	void setUpConnections();
	void addEntry();
};

