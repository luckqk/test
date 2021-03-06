﻿#ifndef QFORMTCPSERVER_H
#define QFORMTCPSERVER_H

#include <QWidget>

#include    <QTcpServer>
#include    <QLabel>

namespace Ui {
class qFormTCPServer;
}

class qFormTCPServer : public QWidget
{
    Q_OBJECT
private:
    QLabel  *LabListen;//状态栏标签
    QLabel  *LabSocketState;//状态栏标签

    QTcpServer *tcpServer; //TCP服务器

    QTcpSocket *tcpSocket;//TCP通讯的Socket

    QString getLocalIP();//获取本机IP地址

protected:
    void    closeEvent(QCloseEvent *event);

public:
    explicit qFormTCPServer(QWidget *parent = nullptr);
    ~qFormTCPServer();

private slots:
//自定义槽函数
    void    onNewConnection();//QTcpServer的newConnection()信号

    void    onSocketStateChange(QAbstractSocket::SocketState socketState);
    void    onClientConnected(); //Client Socket connected
    void    onClientDisconnected();//Client Socket disconnected
    void    onSocketReadyRead();//读取socket传入的数据
//UI生成的
    void    on_actStart_triggered();

    void    on_actStop_triggered();

    void    on_actClear_triggered();

    void    on_btnSend_2_clicked();

    void    on_actHostInfo_triggered();
private:
    Ui::qFormTCPServer *ui;
};

#endif // QFORMTCPSERVER_H
