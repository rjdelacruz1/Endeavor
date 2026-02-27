#include "Commands.h"
#include <QTimer>
Commands::Commands(QObject* parent)
	: QObject(parent)
{
}
void Commands::handle(const QString& input)
{
	const QString cmd = input.trimmed();

	if (cmd.isEmpty())
		return;

	const QString upper = cmd.toUpper();
	if (upper == "EXIT" || upper == "QUIT" || upper == "QQ") {
		exitCommand();
		return;
	}

	if (upper == "TASKS" || upper == "TASK") {
		taskCommand();
		return;
	}
	
	emit outputRequested("Invalid command.");
}
void Commands::exitCommand()
{
	emit outputRequested("Goodbye.");

	QTimer::singleShot(600, this, [this]() {
		emit exitRequested();
		});
}
void Commands::taskCommand(){
	emit tasksRequested("Opening Tasks Window.");
}
