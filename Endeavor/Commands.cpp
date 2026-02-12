#include "Commands.h"
#include <qtimer.h>
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
		Commands::exitCommand();
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
void Commands::taskCommand(){}
