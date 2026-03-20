#pragma once
#include <QObject>
#include <QString>
#include <QHash>
class Commands: public QObject
{
	Q_OBJECT
public:
	explicit Commands(QObject* parent = nullptr);
	void handle(const QString& input);
	void exitCommand();
	void taskCommand();

signals:
	void exitRequested();
	void outputRequested(const QString& line);
	void tasksRequested(const QString& line);
private:
	QHash<QString, QString> commandMap;

	QString resolveCommand(const QString& input) const;
};

