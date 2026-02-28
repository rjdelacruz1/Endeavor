#include "TasksWindow.h"

TasksWindow::TasksWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setTasksWindowSpecifications();

	connect(ui.taskAddEditLineEdit, &QLineEdit::textChanged, this, [this](const QString& t) {
		ui.addButton->setEnabled(!t.trimmed().isEmpty());
		});
	connect(ui.addButton, &QPushButton::clicked, this, [this]() {
		addTaskEntry();
	});
	connect(ui.taskAddEditLineEdit, &QLineEdit::returnPressed, this, [this]() {
		addTaskEntry();
	});
	connect(ui.currentTasksList, &QListWidget::itemChanged, this, [this](QListWidgetItem* item) {
		if (!item)
			return;
		if (item->checkState() == Qt::Checked) {
			moveTaskItem(ui.currentTasksList, ui.completedTasksList, item);
		}
	});
	connect(ui.oldTasksList, &QListWidget::itemChanged, this, [this](QListWidgetItem* item) {
		if (!item)
			return;
		if (item->checkState() == Qt::Checked) {
			moveTaskItem(ui.oldTasksList, ui.completedTasksList, item);
		}
	});
	connect(ui.completedTasksList, &QListWidget::itemChanged, this, [this](QListWidgetItem* item) {
		if (!item)
			return;
		if (item->checkState() == Qt::Unchecked) {
			moveTaskItem(ui.completedTasksList, ui.currentTasksList, item);
		}
	});
	connect(ui.currentTasksList, &QListWidget::itemSelectionChanged, this, [this]() {
		auto* item = ui.currentTasksList->currentItem();
		if (!item)
			return;

		ui.taskAddEditLineEdit->setText(item->text());
		ui.taskAddEditLineEdit->setFocus();
		ui.taskAddEditLineEdit->setCursorPosition(ui.taskAddEditLineEdit->text().length());
	});
}
void TasksWindow::setTasksWindowSpecifications()
{
	this->ui.taskAddEditLineEdit->setFocus();
	this->ui.addButton->setEnabled(false);
	this->setStyleSheet(R"(
		QLabel, QLineEdit, QListWidget{
			border: 1px solid;
		}
	)");
	/*
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
	GET RID OF THIS LATER
	*/
}
void TasksWindow::addTaskEntry() {
	QString text = ui.taskAddEditLineEdit->text().trimmed();
	if (text.isEmpty())
		return;
	
	auto *item = new QListWidgetItem(text);
	item->setFlags(item->flags()|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	item->setCheckState(Qt::Unchecked);
	ui.currentTasksList->addItem(item);

	ui.taskAddEditLineEdit->clear();
	ui.taskAddEditLineEdit->setFocus();
}
void TasksWindow::moveTaskItem(QListWidget* from, QListWidget* to, QListWidgetItem* item) {
	if (!from || !to || !item)
		return;

	QSignalBlocker BlockFrom(from);
	QSignalBlocker BlockTo(to);

	const QString text = item->text();
	const Qt::CheckState state = item->checkState();

	const int row = from->row(item);
	delete from->takeItem(row);

	auto* newItem = new QListWidgetItem(text);
	
	if (to == ui.completedTasksList) {
		newItem->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		QFont font = newItem->font();
		font.setStrikeOut(true);
		newItem->setFont(font);
		newItem->setCheckState(state);
		to->insertItem(0,newItem);
	}
	else {
		newItem->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		newItem->setCheckState(state);
		to->addItem(newItem);
	}

	
}
TasksWindow::~TasksWindow()
{}

