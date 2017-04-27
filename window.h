#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVector>
#include <QFile>

#include "database.h"

class Window : public QDialog
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
        void Layout();
        QPushButton *button(QString title);
        QLineEdit *edit(QString title);
        QTableWidget *table(QString day);

        void TableInputing(QTableWidget *table, QVector<QVector<QString> > &data, QString day);

private:
        QVector<QTableWidget*> tables;
        Database *database;
        QComboBox *box, *variants, *groups;
        QLineEdit *group, *id, *name, *search_value;

private slots:
                void buttonClick();

};

#endif // WINDOW_H
