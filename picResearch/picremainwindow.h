#ifndef PICREMAINWINDOW_H
#define PICREMAINWINDOW_H

#include <QMainWindow>

#include  "qformdoc.h"
#include  "qformtcp.h"
#include  "qformtcpserver.h"

namespace Ui {
class PicReMainWindow;
}

class PicReMainWindow : public QMainWindow
{
    Q_OBJECT
private:
    //绘制窗口背景图片 QFormTable  *formTable=NULL; //
    void  paintEvent(QPaintEvent *event);
public:
    explicit PicReMainWindow(QWidget *parent = nullptr);
    ~PicReMainWindow();

private slots:
    void on_tabWidget_tabCloseRequested(int index);

//    void on_actDoc_Open_triggered();

//    void on_actWidgetWindow_triggered();

    void on_actWidgetInsite_triggered();

    //void on_actWindowInsite_triggered();

    void on_actTCPClient_triggered();

    void on_actTCPServer_triggered();

    void on_actWidget_triggered();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::PicReMainWindow *ui;
};

#endif // PICREMAINWINDOW_H
