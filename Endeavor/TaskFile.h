#pragma once
#include "Task.h"
#include <QVector>
#include <QString>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QDir>

class TaskFile
{
	public:
		bool load(const QString& path);
		bool save(const QString& path) const;
		QString taskFilePath() const;

		QVector<Task> tasks;
};

