#pragma once
#include "Log.h"
#include <QString>
#include <QVector>
#include <QMap>
#include <QDir>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

class LogFile
{
public:
	bool load(const QString& path);
	bool save(const QString& path) const;
	QString logFilePath() const;

	QMap<QDate, Log> logs;
};

