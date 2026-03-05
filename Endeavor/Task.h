#pragma once
#include <QDateTime>
#include <QString>
#include <QJsonObject>

struct Task {
	QString text;
	QDateTime date;
	bool completed = false;

	QJsonObject toJson() const{
		QJsonObject obj;
		obj["text"] = text;
		obj["date"] = date.toString(Qt::ISODate);
		obj["completed"] = completed;
		return obj;
	}

	static Task fromJson(const QJsonObject& obj) {
		Task t;
		t.text = obj["text"].toString();
		t.date = QDateTime::fromString(obj["date"].toString(), Qt::ISODate);
		t.completed = obj["completed"].toBool(false);
		return t;
	}
};