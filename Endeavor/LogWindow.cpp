#include "LogWindow.h"

LogWindow::LogWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	logPath = logFile.logFilePath();
	setLogWindowSpecifications();
	setUpConnections();
}
void LogWindow::setLogWindowSpecifications() {
	this->ui.logEditBox->setFocus();
	this->ui.addLog->setEnabled(false);

	this->setStyleSheet(R"(
		QLabel, QPlainTextEdit, QListWidget{
			border: 1px solid;
		}
	)");

}
void LogWindow::setUpConnections() {
	connect(ui.logEditBox, &QPlainTextEdit::textChanged, this, [this]() {
		ui.addLog->setEnabled(!ui.logEditBox->toPlainText().trimmed().isEmpty());
	});
	connect(ui.addLog, &QPushButton::clicked, this, &LogWindow::addEntry);
}
void LogWindow::addEntry() {
	QString text = ui.logEditBox->toPlainText().trimmed();
	if (text.isEmpty())
		return;

	QDate date = QDate::currentDate();

	logFile.logs[date] = Log(text, date);

	//populateLogList();
	logFile.save(logPath);

	ui.logEditBox->clear();
	ui.logEditBox->setFocus();
	ui.addLog->setEnabled(false);
}
LogWindow::~LogWindow()
{}

