#include "TasksWindow.h"

TasksWindow::TasksWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setTasksWindowSpecifications();
}
void TasksWindow::setTasksWindowSpecifications()
{
	ui.currentTasksLabel->setStyleSheet(R"(
		QLabel{
			border: 1px solid;
		}
	)");
	ui.currentTasksList->setStyleSheet(R"(
		QListWidget{
			border: 1px solid;
		}
	)");

	ui.oldTasksLabel->setStyleSheet(R"(
		QLabel{
			border: 1px solid;
		}
	)");
	ui.oldTasksList->setStyleSheet(R"(
		QListWidget{
			border: 1px solid;
		}
	)");

	ui.completedTasksLabel->setStyleSheet(R"(
		QLabel{
			border: 1px solid;
		}
	)");
	ui.completedTasksList->setStyleSheet(R"(
		QListWidget{
			border: 1px solid;
		}
	)");

	ui.commandEntry->setStyleSheet(R"(
		QLineEdit{
			border: 1px solid;
		}
	)");
}
TasksWindow::~TasksWindow()
{}

