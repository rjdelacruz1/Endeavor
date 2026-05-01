#include "Commands.h"
#include <QTimer>
Commands::Commands(QObject* parent)
	: QObject(parent)
{
	commandMap["EXIT"] = "EXIT";
	commandMap["QUIT"] = "EXIT";
	commandMap["QQ"] = "EXIT";

	commandMap["HELP"] = "HELP";

	commandMap["TASK"] = "TASK";
	commandMap["TASKS"] = "TASK";

	commandMap["LOG"] = "LOG";
	commandMap["DIARY"] = "LOG";

}
void Commands::handle(const QString& input)
{
	const QString cmd = input.trimmed();

	if (cmd.isEmpty())
		return;

	const QString upper = resolveCommand(cmd);
	if (upper == "EXIT") {
		exitCommand();
		return;
	}

	if (upper == "TASK") {
		taskCommand();
		return;
	}

	if (upper == "LOG") {
		logCommand();
		return;
	}

	if (upper == "HELP") {
		
		return;
	}
	
	emit outputRequested("Invalid command.");
}
QString Commands::resolveCommand(const QString& input) const {
	const QString upper = input.toUpper();

	if (commandMap.contains(upper))
		return commandMap.value(upper);

	return upper;
}
void Commands::helpCommand() {

}
void Commands::exitCommand()
{
	emit outputRequested("Goodbye.");

	QTimer::singleShot(600, this, [this]() {
		emit exitRequested();
		});
}
void Commands::taskCommand(){
	emit outputRequested("Opening Tasks Window.");
	
	QTimer::singleShot(600, this, [this]() {
		emit tasksRequested();
		});
}
void Commands::logCommand() {
	emit outputRequested("Opening Log Window.");

	QTimer::singleShot(600, this, [this]() {
		emit logRequested();
		});
}
