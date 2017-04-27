#include "database.h"

Database::Database()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("timetable");
    db.setUserName("Ulyana");
    db.setPassword("0000");
    db.setHostName("localhost");

    if(!db.open())
        qDebug() << "Can not open db manager";

    query = new QSqlQuery(db);
}

Database::~Database()
{

}

void Database::CreateTable(QString name)
{
    QString table = "CREATE TABLE " + name + "("
                                             "id VARCHAR(10),"
                                             "FeI21 VARCHAR(20),"
                                             "FeI22 VARCHAR(20)"
                                             ");";
    if(!query->exec(table))
        qDebug() << "Unable to create table!";

    for(int i=0; i<5; i++)
        Inputing(name);
}

void Database::Inputing(QString table)
{
    QString tamplate = "INSERT INTO " + table + "(id, FeI21, FeI22)"
                       "VALUES('%1', '%2', '%3');";

    static int i = 1;
    QString command = tamplate.arg(QString::number(i))
                        .arg(" ")
                        .arg(" ");

    i++;
    if(i == 6) i = 1;

    if(!query->exec(command))
        qDebug() << "Error with inputing data!";
}

void Database::Updating(const QString &id, const QString &group, const QString &name, QString table)
{
    QString command = "UPDATE " + table + " SET " + group + "= \""
            + name + "\" WHERE id = \""+ id +"\";";

    if(!query->exec(command))
        qDebug() << "Error with updating data!";
}

QVector<QVector<QString> > &Database::Reading(QString table, int index)
{
    data.clear();

    if(!index)
    {
        if(!query->exec("SELECT id, FeI21 FROM " + table + ";"))
            qDebug() << "Unable to read data!";
    }
    else
    {
        if(!query->exec("SELECT id, FeI22 FROM " + table + ";"))
            qDebug() << "Unable to read data!";
    }

    while(query->next())
    {
        QVector<QString> row;

        for(int i=0; i<2; i++)
            row.push_back(query->value(i).toString());

        data.push_back(row);
    }

    return data;
}

QVector<QVector<QString> > &Database::Searching(QString table, const QString &value, int variant, int index)
{
    data.clear();

    if(!index)
    {
        if(!variant)
        {
            if(!query->exec("SELECT id, FeI21 FROM " + table + " WHERE id = \"" + value + "\";"))
                qDebug() << "Unable to search data!";
        }
        else
        {
            if(!query->exec("SELECT id, FeI21 FROM " + table + " WHERE FeI21 = \"" + value + "\";"))
                qDebug() << "Unable to search data!";
        }
    }
    else
    {
        if(!variant)
        {
            if(!query->exec("SELECT id, FeI22 FROM " + table + " WHERE id = \"" + value + "\";"))
                qDebug() << "Unable to search data!";
        }
        else
        {
            if(!query->exec("SELECT id, FeI22 FROM " + table + " WHERE FeI22 = \"" + value + "\";"))
                qDebug() << "Unable to search data!";
        }
    }

    while(query->next())
    {
        QVector<QString> row;

        for(int i=0; i<2; i++)
            row.push_back(query->value(i).toString());

        data.push_back(row);
    }

    return data;
}
