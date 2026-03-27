#include "LogFile.h"

bool LogFile::save(const QString& path) const
{
	QJsonArray arr;
	for (auto i = logs.cbegin(); i != logs.cend(); ++i)
		arr.append(i.value().toJson());

	QJsonDocument doc(arr);

	QFile f(path);
	if (!f.open(QIODevice::WriteOnly))
		return false;

	f.write(doc.toJson(QJsonDocument::Indented));
	return true;
}
bool LogFile::load(const QString& path)
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

	logs.clear();
	for (const auto& v : doc.array()) {
		if (!v.isObject())
			continue;

		Log logEntry = Log::fromJson(v.toObject());
		if (logEntry.date.isValid())
			logs[logEntry.date] = logEntry;
	}
	return true;
}

QString LogFile::logFilePath() const {
	const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
	QDir().mkpath(dir);
	return dir + "/logs.json";
};
