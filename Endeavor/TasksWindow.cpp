#include "TasksWindow.h"
#include <QDebug>
#include <QMessagebox>

TasksWindow::TasksWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setTasksWindowSpecifications();
	taskPath = taskFile.taskFilePath();
	taskFile.load(taskPath);
	populateLists(taskFile.tasks);

	qDebug() << taskFile.taskFilePath();
	setUpConnections();
	//QMessageBox::information(this, "Path", taskFile.taskFilePath());


	/*
	//Enables addButton when text is entered into the line edit
	connect(ui.taskAddEditLineEdit, &QLineEdit::textChanged, this, [this](const QString& t) {
		ui.addButton->setEnabled(!t.trimmed().isEmpty());
		});
	//Adds click functionality to addButton
	connect(ui.addButton, &QPushButton::clicked, this, [this]() {
		addTaskEntry();
	});
	//Adds enter key functionality to QLineEdit
	connect(ui.taskAddEditLineEdit, &QLineEdit::returnPressed, this, [this]() {
		addTaskEntry();
	});

	//The following two connect calls allow for tasks in the currentTasksList and oldTasksList respectively to move
	//to the completedTasksList once they are checked. The 3rd connect call allows items in the completedTasksList
	//to move back to the currentTasksList.
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

	//Allows editing of selected items in the currentTasksList by populating the taskAddEditLineEdit once a task
	//is highlighted.
	connect(ui.currentTasksList, &QListWidget::itemSelectionChanged, this, [this]() {
		auto* item = ui.currentTasksList->currentItem();
		if (!item)
			return;

		ui.taskAddEditLineEdit->setText(item->text());
		ui.taskAddEditLineEdit->setFocus();
		ui.taskAddEditLineEdit->setCursorPosition(ui.taskAddEditLineEdit->text().length());
	});
	*/
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
void TasksWindow::setUpConnections() {
	//Enables addButton when text is entered into the line edit
	connect(ui.taskAddEditLineEdit, &QLineEdit::textChanged, this, [this](const QString& t) {
		const bool hasText = !(t.trimmed().isEmpty());
		ui.addButton->setEnabled(itemBeingEdited==nullptr && hasText);
		});
	//Adds click functionality to addButton
	connect(ui.addButton, &QPushButton::clicked, this, [this]() {
		addTaskEntry();
		});
	//Adds enter key functionality to QLineEdit
	connect(ui.taskAddEditLineEdit, &QLineEdit::returnPressed, this, [this]() {
		if (itemBeingEdited)
			confirmEdit();
		else 
			addTaskEntry();
		
		});

	//The following two connect calls allow for tasks in the currentTasksList and oldTasksList respectively to move
	//to the completedTasksList once they are checked. The 3rd connect call allows items in the completedTasksList
	//to move back to the currentTasksList.
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

	//
	connect(ui.currentTasksList, &QListWidget::itemSelectionChanged, this, &TasksWindow::handleListSelection);
	connect(ui.oldTasksList, &QListWidget::itemSelectionChanged, this, &TasksWindow::handleListSelection);
	
	//Confirm Edit connection
	connect(ui.confirmEdit, &QPushButton::clicked, this, &TasksWindow::confirmEdit);
	
	//Cancel Edit connection
	connect(ui.cancelEdit, &QPushButton::clicked, this, &TasksWindow::exitEditMode);

}
void TasksWindow::addTaskEntry() {
	QString text = ui.taskAddEditLineEdit->text().trimmed();
	if (text.isEmpty())
		return;
	
	auto *item = new QListWidgetItem(text);
	item->setFlags(item->flags()|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	item->setCheckState(Qt::Unchecked);
	ui.currentTasksList->insertItem(0,item);

	Task t(text, QDateTime::currentDateTime(), false);
	taskFile.tasks.append(t);
	taskFile.save(taskPath);

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
	const Qt::ItemFlags flags = item->flags();
	delete from->takeItem(row);

	auto* newItem = new QListWidgetItem(text);
	
	if (to == ui.completedTasksList) {
		newItem->setFlags(flags | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		QFont font = newItem->font();
		font.setStrikeOut(true);
		newItem->setFont(font);
		newItem->setCheckState(state);
		to->insertItem(0,newItem);
	}
	else {
		newItem->setFlags(flags | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		newItem->setCheckState(state);
		to->addItem(newItem);
	}

	
}
void TasksWindow::populateLists(const QVector<Task>& v)
{
	ui.completedTasksList->clear();
	ui.currentTasksList->clear();
	ui.oldTasksList->clear();
	for (const Task& t : v)
	{
		const QString text = t.text;
		auto* item = new QListWidgetItem(text);
		item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		QFont font = item->font();
		if (t.completed==true)
		{
			font.setStrikeOut(true);
			item->setFont(font);
			item->setCheckState(Qt::Checked);
			ui.completedTasksList->addItem(item);
		}else if(t.date.date().daysTo(QDate::currentDate())>7)
		{
			item->setCheckState(Qt::Unchecked);
			ui.oldTasksList->addItem(item);
		}else
		{
			item->setCheckState(Qt::Unchecked);
			ui.currentTasksList->addItem(item);
		}
	}
}
void TasksWindow::handleListSelection() {
	auto* list = qobject_cast<QListWidget*>(sender());
	if (!list)
		return;

	auto* item = list->currentItem();
	if (!item)
		return;
	
	enterEditMode(item);

	if (list == ui.currentTasksList)
		ui.oldTasksList->clearSelection();
	else if (list == ui.oldTasksList)
		ui.currentTasksList->clearSelection();
}
void TasksWindow::enterEditMode(QListWidgetItem* item) {
	if (!item)
		return;
	if (itemBeingEdited == item)
		return;

	itemBeingEdited = item;

	ui.taskAddEditLineEdit->setText(item->text());
	ui.taskAddEditLineEdit->selectAll();
	ui.taskAddEditLineEdit->setFocus();
	//ui.taskAddEditLineEdit->setCursorPosition(ui.taskAddEditLineEdit->text().length());

	ui.addButton->setEnabled(false);
	ui.confirmEdit->setEnabled(true);
}
void TasksWindow::confirmEdit() {
	if (!itemBeingEdited)
		return;
	QString text = ui.taskAddEditLineEdit->text().trimmed();

	if (text.isEmpty())
		return;

	itemBeingEdited->setText(text);
	exitEditMode();
}
void TasksWindow::exitEditMode() {
	itemBeingEdited = nullptr;

	{
		QSignalBlocker blockCurrent(ui.currentTasksList);
		QSignalBlocker blockOld(ui.oldTasksList);

		ui.currentTasksList->clearSelection();
		ui.oldTasksList->clearSelection();

		ui.currentTasksList->setCurrentItem(nullptr);
		ui.oldTasksList->setCurrentItem(nullptr);
	}

	ui.taskAddEditLineEdit->clear();
	

	ui.addButton->setEnabled(true);
	ui.confirmEdit->setEnabled(false);
}
TasksWindow::~TasksWindow()
{}
//Test code for populatingLists method
/*
	//Following code is for testing populateLists method
	Task t1;
	t1.text = "Test Current Task";
	t1.date = QDateTime::currentDateTime();
	t1.completed = false;

	Task t2;
	t2.text = "Test Old Task";
	t2.date = QDateTime::currentDateTime().addDays(-10);
	t2.completed = false;

	Task t3;
	t3.text = "Test Completed Task";
	t3.date = QDateTime::currentDateTime();
	t3.completed = true;

	taskFile.tasks = { t1, t2, t3 };
	taskFile.save(taskPath);
	//End of populateList method test data (delete later and populate folder with more test data)
	*/

