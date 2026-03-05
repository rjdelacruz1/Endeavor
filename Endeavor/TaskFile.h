#pragma once
#include "Task.h"
#include <QVector>
#include <QString>
class TaskFile
{
	public:
		bool load(const QString& path);
		bool save(const QString& path) const;
		QString taskFilePath() const;

		QVector<Task> tasks;
};

