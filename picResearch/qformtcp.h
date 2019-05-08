#ifndef QFORMTCP_H
#define QFORMTCP_H

#include <QWidget>
#include <QTcpSocket>
#include <QLabel>

namespace Ui {
class qFormTCP;
}

class qFormTCP : public QWidget
{
    Q_OBJECT
private:
    QTcpSocket  *tcpClient;  //socket
    QLabel      *LabSocketState;  //状态栏显示标签

    QString     getLocalIP();//获取本机IP地址
protected:
    void    closeEvent(QCloseEvent *event);

public:
    explicit qFormTCP(QWidget *parent = nullptr);
    ~qFormTCP();

private slots:
    void    onConnected();
    void    onDisconnected();
    void    onSocketStateChange(QAbstractSocket::SocketState socketState);
    void    onSocketReadyRead();//读取socket传入的数据

    void on_actConnect_triggered();

    void on_actDisconnect_triggered();

    void on_actClear_triggered();

    void on_btnSend_clicked();

private:
    Ui::qFormTCP *ui;
};

#endif // QFORMTCP_H
