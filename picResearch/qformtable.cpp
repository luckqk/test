#include "qformtable.h"
#include "ui_qformtable.h"

QFormTable::QFormTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFormTable)
{
    ui->setupUi(this);
}

QFormTable::~QFormTable()
{
    delete ui;
}
