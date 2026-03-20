#include "Commands.h"
#include <QTimer>
Commands::Commands(QObject* parent)
	: QObject(parent)
{
	commandMap["EXIT"] = "EXIT";
	commandMap["QUIT"] = "EXIT";
	commandMap["QQ"] = "EXIT";

	commandMap["TASK"] = "TASK";
	commandMap["TASKS"] = "TASK";
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
	
	emit outputRequested("Invalid command.");
}
QString Commands::resolveCommand(const QString& input) const {
	const QString upper = input.toUpper();

	if (commandMap.contains(upper))
		return commandMap.value(upper);

	return upper;
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
