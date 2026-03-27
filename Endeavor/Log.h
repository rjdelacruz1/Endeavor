#pragma once
#include <QDateTime>
#include <QJsonObject>
#include <QString>

struct Log {
	QDate date;
	QString log;

	Log() = default;
	Log(QString log, QDate date)
		: log(log), date(date) {}

	QJsonObject toJson() const {
		QJsonObject obj;
		obj["log"] = log;
		obj["date"] = date.toString(Qt::ISODate);
		return obj;
	}

	static Log fromJson(const QJsonObject& obj) {
		Log l;
		l.log = obj["log"].toString();
		l.date = QDate::fromString(obj["date"].toString(), Qt::ISODate);
		return l;
	}
};
