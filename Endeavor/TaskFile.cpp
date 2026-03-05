#include "TaskFile.h"
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QDir>


bool TaskFile::save(const QString& path) const 
{
	QJsonArray arr;
	for (const auto& t : tasks)
		arr.append(t.toJson());

	QJsonDocument doc(arr);

	QFile f(path);
	if(!f.open(QIODevice::WriteOnly))
		return false;

	f.write(doc.toJson(QJsonDocument::Indented));
	return true;
}
bool TaskFile::load(const QString& path)
{
	QFile f(path);
	if (!f.exists())
		return false;

	if (!f.open(QIODevice::ReadOnly))
		return false;

	const QByteArray data = f.readAll();

	QJsonParseError err{};
	const QJsonDocument doc = QJsonDocument::fromJson(data, &err);
	if (err.error != QJsonParseError::NoError || !doc.isArray())
		return false;

	tasks.clear();
	for (const auto& v : doc.array()) {
		if (v.isObject())
			tasks.push_back(Task::fromJson(v.toObject()));
	}
	return true;
}
QString TaskFile::taskFilePath() const
{
	const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	QDir().mkpath(dir);
	return dir + "/tasks.json";
}
