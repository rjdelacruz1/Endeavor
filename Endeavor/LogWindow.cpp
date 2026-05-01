#include "LogWindow.h"

LogWindow::LogWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	logPath = logFile.logFilePath();
	logFile.load(logPath);
	populateLogList();
	setLogWindowSpecifications();
	setUpConnections();
}
void LogWindow::setLogWindowSpecifications() {
	this->ui.logEditBox->setFocus();
	this->ui.addLog->setEnabled(false);

	this->setStyleSheet(R"(
		QPlainTextEdit, QListWidget{
			border: 1px solid;
		}
	)");

}
void LogWindow::setUpConnections() {
	connect(ui.logEditBox, &QPlainTextEdit::textChanged, this, [this]() {
		ui.addLog->setEnabled(!ui.logEditBox->toPlainText().trimmed().isEmpty());
	});
	connect(ui.addLog, &QPushButton::clicked, this, &LogWindow::addEntry);

	connect(ui.logList,&QListWidget::itemSelectionChanged,this, &LogWindow::loadLogListEntry);

	connect(ui.cancelEdit, &QPushButton::clicked, this, &LogWindow::cancelEdit);

	connect(ui.confirmEdit, &QPushButton::clicked, this, &LogWindow::confirmEdit);
}
void LogWindow::addEntry() {
	QString text = ui.logEditBox->toPlainText().trimmed();
	if (text.isEmpty())
		return;

	QDate date = QDate::currentDate();

	if (logFile.logs.contains(date)) {
		Log& existing = logFile.logs[date];
		if (!existing.log.isEmpty())
			existing.log += "\n\n";

		existing.log += text;
	}
	else 
	{
		logFile.logs[date] = Log(text, date);
	}
	
	populateLogList(date);
	logFile.save(logPath);

	ui.logEditBox->clear();
	ui.logEditBox->setFocus();
	ui.addLog->setEnabled(false);
}
void LogWindow::confirmEdit() {
	QListWidgetItem* currentSelectedItem = ui.logList->currentItem();
	if (!currentSelectedItem)
		return;

	QDate date = currentSelectedItem->data(Qt::UserRole).toDate();
	if (!date.isValid())
		return;

	if (!logFile.logs.contains(date))
		return;

	QString editedText = ui.logPreviewEdit->toPlainText().trimmed();
	if (editedText.isEmpty())
		return;

	logFile.logs[date].log = editedText;

	logFile.save(logPath);
	populateLogList(date);
}
void LogWindow::populateLogList(const QDate& selectedDate) {
	ui.logList->clear();

	auto keys = logFile.logs.keys();
	for (int i = keys.size() - 1; i >= 0; --i)
	{
		QDate date = keys[i];

		auto* item = new QListWidgetItem(date.toString("MMM d, yyyy"));
		item->setData(Qt::UserRole, date);
		ui.logList->addItem(item);

		if (date == selectedDate)
			ui.logList->setCurrentItem(item);
	}
}
void LogWindow::populateLogList() {
	ui.logList->clear();

	auto keys = logFile.logs.keys();
	for (int i = keys.size() - 1; i >= 0; --i)
	{
		QDate date = keys[i];

		auto* item = new QListWidgetItem(date.toString("MMM d, yyyy"));
		item->setData(Qt::UserRole, date);
		ui.logList->addItem(item);
	}
}
void LogWindow::loadLogListEntry() {
	QListWidgetItem* item = ui.logList->currentItem();
	if (!item)
		return;

	QDate date = item->data(Qt::UserRole).toDate();

	if (logFile.logs.contains(date))
		ui.logPreviewEdit->setPlainText(logFile.logs[date].log);
}
void LogWindow::cancelEdit() {
	ui.logEditBox->clear();
	ui.logList->clearSelection();
	ui.logPreviewEdit->clear();
	ui.logList->setCurrentItem(nullptr);
	ui.addLog->setEnabled(false);
	ui.logEditBox->setFocus();
}

LogWindow::~LogWindow()
{}

