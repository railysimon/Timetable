#include "window.h"

Window::Window(QWidget *parent): QDialog(parent)
{
    Layout();

    bool exist = false;
    if(QFile::exists("timetable")) exist = true;
    database = new Database;

    if(!exist)
    {
        QString days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

        for(int i=0; i<5; i++)
            database->CreateTable(days[i]);
    }
}

Window::~Window()
{

}

void Window::Layout()
{
    box = new QComboBox;
    QStringList list;
    list << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday";
    box->addItems(list);
    box->setStyleSheet("font-weight: bold;");

    QLabel *type = new QLabel("New type");
    type->setFont(QFont("Ubuntu", 12, QFont::Bold));

    QLabel *searching = new QLabel("Search");
    searching->setFont(QFont("Ubuntu", 12, QFont::Bold));

    variants = new QComboBox;
    list.clear();
    list << "Number" << "Name";
    variants->addItems(list);
    variants->setStyleSheet("font-weight: bold;");

    groups = new QComboBox;
    list.clear();
    list << "FeI21" << "FeI22";
    groups->addItems(list);
    groups->setStyleSheet("font-weight: bold;");

    QVBoxLayout *left_layer = new QVBoxLayout;
    left_layer->setAlignment(Qt::AlignRight | Qt::AlignTop);
    left_layer->addSpacing(20);
    left_layer->addWidget(type);
    left_layer->addSpacing(10);
    left_layer->addWidget(box);
    left_layer->addSpacing(10);

    group = edit("Group");
    left_layer->addWidget(group);
    left_layer->addSpacing(10);

    id = edit("Number");
    left_layer->addWidget(id);
    left_layer->addSpacing(10);

    name = edit("Name");
    left_layer->addWidget(name);
    left_layer->addSpacing(10);
    left_layer->addWidget(button("Add"));

    left_layer->addSpacing(20);
    left_layer->addWidget(searching);
    left_layer->addSpacing(10);
    left_layer->addWidget(variants);
    left_layer->addSpacing(10);

    search_value = edit("Value");
    left_layer->addWidget(search_value);
    left_layer->addSpacing(10);

    left_layer->addWidget(button("Search"));
    left_layer->addSpacing(150);
    left_layer->addWidget(groups);
    left_layer->addWidget(button("Show"));

    QVBoxLayout *table_layer = new QVBoxLayout;
    QHBoxLayout *table_layer_first = new QHBoxLayout;
    QHBoxLayout *table_layer_second = new QHBoxLayout;

    QString days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    for(int i=0; i<3; i++)
        table_layer_first->addWidget(table(days[i]));

    for(int i=3; i<5; i++)
        table_layer_second->addWidget(table(days[i]));

    table_layer->addLayout(table_layer_first);
    table_layer->addLayout(table_layer_second);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addLayout(table_layer);
    layout->addLayout(left_layer);
    this->setLayout(layout);
    this->setFixedSize(800, 600);
    this->setStyleSheet("background: rgb(82, 67, 67); color: white;");
}

QPushButton *Window::button(QString title)
{
    QPushButton *btn = new QPushButton(title);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet("QPushButton { font-weight: bold; background: rgb(73, 71, 91); }"
                       "QPushButton:hover { background: rgb(102, 181, 136); }");

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClick()));

    return btn;
}

QLineEdit *Window::edit(QString title)
{
    QLineEdit *line = new QLineEdit(title);
    line->setFixedWidth(150);
    line->setStyleSheet("background: white; color: black;");

    return line;
}

QTableWidget *Window::table(QString day)
{
    QTableWidget *tabl = new QTableWidget(5, 2);
    tabl->setColumnWidth(0, 30);
    tabl->setColumnWidth(1, 170);
    tabl->setFixedSize(200, 170);
    tabl->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tabl->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tabl->setStyleSheet("font-weight: bold;");

    QStringList list;
    list << "№" << day;
    tabl->setHorizontalHeaderLabels(list);

    list.clear();
    list << "" << "" << "" << "" << "";
    tabl->setVerticalHeaderLabels(list);

    tables.push_back(tabl);
    return tabl;
}

void Window::TableInputing(QTableWidget *table, QVector<QVector<QString> > &data, QString day)
{   
    table->clear();

    QStringList list;
    list << "№" << day;
    table->setHorizontalHeaderLabels(list);

    list.clear();
    list << "" << "" << "" << "" << "";
    table->setVerticalHeaderLabels(list);

    QTableWidgetItem *item;
    for(int i=0; i<data.size(); i++)
        for(int j=0; j<2; j++)
        {
            item = new QTableWidgetItem(data[i][j]);
            table->setItem(i, j, item);
        }
}

void Window::buttonClick()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    QVector<QVector<QString> > data;

    if(btn->text() == "Show")
    {
        for(int i=0; i<tables.size(); i++)
        {
            data = database->Reading(days[i], groups->currentIndex());
            TableInputing(tables[i], data, days[i]);
        }
    }

    if(btn->text() == "Add")
    {
        database->Updating(id->text(), group->text(), name->text(), days[box->currentIndex()]);
    }

    if(btn->text() == "Search")
    {
        for(int i=0; i<tables.size(); i++)
        {
            data = database->Searching(days[i], search_value->text(), variants->currentIndex(), groups->currentIndex());
            TableInputing(tables[i], data, days[i]);
        }
    }
}
