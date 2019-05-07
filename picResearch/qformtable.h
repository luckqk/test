#ifndef QFORMTABLE_H
#define QFORMTABLE_H

#include <QWidget>

namespace Ui {
class QFormTable;
}

class QFormTable : public QWidget
{
    Q_OBJECT

public:
    explicit QFormTable(QWidget *parent = nullptr);
    ~QFormTable();

private:
    Ui::QFormTable *ui;
};

#endif // QFORMTABLE_H
