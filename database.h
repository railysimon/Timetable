#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QVector>

class Database
{
public:
        Database();
        ~Database();

        void CreateTable(QString name);
        void Inputing(QString table);
        void Updating(const QString &id, const QString &group, const QString &name, QString table);
        QVector<QVector<QString> > &Reading(QString table, int index);
        QVector<QVector<QString> > &Searching(QString table, const QString &value, int variant, int index);

private:
        QSqlQuery *query;
        QVector<QVector <QString> > data;
};

#endif // DATABASE_H
