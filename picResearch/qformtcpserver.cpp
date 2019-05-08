/**********************************
 * TCP服务端功能代码
 * 20190508
 * *******************************/

#include "qformtcpserver.h"
#include "ui_qformtcpserver.h"

#include    <QToolBar>
#include    <QFileInfo>
#include    <QHostAddress>
#include    <QHostInfo>
#include    <QtNetwork>

#include    <picremainwindow.h>

//获取本机IPv4地址
QString qFormTCPServer::getLocalIP()
{
    QString hostName=QHostInfo::localHostName();//本地主机名
    QHostInfo   hostInfo=QHostInfo::fromName(hostName);
    QString   localIP="";

    QList<QHostAddress> addList=hostInfo.addresses();//

    if (!addList.isEmpty())
    for (int i=0;i<addList.count();i++)
    {
        QHostAddress aHost=addList.at(i);
        if (QAbstractSocket::IPv4Protocol==aHost.protocol())
        {
            localIP=aHost.toString();
            break;
        }
    }
    return localIP;
}

//关闭窗口时停止监听
void qFormTCPServer::closeEvent(QCloseEvent *event)
{
    if (tcpServer->isListening())
        tcpServer->close();;//停止网络监听
    event->accept();
}

qFormTCPServer::qFormTCPServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qFormTCPServer)
{
    ui->setupUi(this);
    //使用UI设计的Actions设计工具栏
    QToolBar* locToolBar = new QToolBar(tr("文档"),this); //创建工具栏
    locToolBar->addAction(ui->actStart);
    locToolBar->addAction(ui->actStop);
    locToolBar->addAction(ui->actClear);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->actQuit);

    locToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    LabListen=new QLabel(QStringLiteral("监听状态:"));
    LabListen->setMinimumWidth(150);//设定语句的最小宽度

    LabSocketState=new QLabel(QStringLiteral("Socket状态："));
    LabSocketState->setMinimumWidth(200);

    QString localIP=getLocalIP();//本机IP
    this->setWindowTitle(this->windowTitle()+QStringLiteral("----本机IP：")+localIP);
    ui->comboIP_2->addItem(localIP);
    //创建 TCP Server
    tcpServer=new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
}

qFormTCPServer::~qFormTCPServer()
{
    delete ui;
}

//    ui->plainTextEdit->appendPlainText("有新连接");
void qFormTCPServer::onNewConnection()
{
    //创建socket,接受客户端的连接
    tcpSocket = tcpServer->nextPendingConnection();

    connect(tcpSocket, SIGNAL(connected()),
            this, SLOT(onClientConnected()));
    onClientConnected();//客户端接入时显示信息

    connect(tcpSocket, SIGNAL(disconnected()),
            this, SLOT(onClientDisconnected()));

    connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this,SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
    onSocketStateChange(tcpSocket->state());

    connect(tcpSocket,SIGNAL(readyRead()),
            this,SLOT(onSocketReadyRead()));
}

//socket状态变化时
void qFormTCPServer::onSocketStateChange(QAbstractSocket::SocketState socketState)
{
    switch(socketState)
    {
    case QAbstractSocket::UnconnectedState:
        LabSocketState->setText(QStringLiteral("scoket状态：UnconnectedState"));
        break;
    case QAbstractSocket::HostLookupState:
        LabSocketState->setText(QStringLiteral("scoket状态：HostLookupState"));
        break;
    case QAbstractSocket::ConnectingState:
        LabSocketState->setText(QStringLiteral("scoket状态：ConnectingState"));
        break;

    case QAbstractSocket::ConnectedState:
        LabSocketState->setText(QStringLiteral("scoket状态：ConnectedState"));
        break;

    case QAbstractSocket::BoundState:
        LabSocketState->setText(QStringLiteral("scoket状态：BoundState"));
        break;

    case QAbstractSocket::ClosingState:
        LabSocketState->setText(QStringLiteral("scoket状态：ClosingState"));
        break;

    case QAbstractSocket::ListeningState:
        LabSocketState->setText(QStringLiteral("scoket状态：ListeningState"));
    }
}

//客户端接入时
void qFormTCPServer::onClientConnected()
{
    ui->plainTextEdit->appendPlainText("**client socket connected");
    ui->plainTextEdit->appendPlainText("**peer address:"+
                                   tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**peer port:"+
                                   QString::number(tcpSocket->peerPort()));
}

//客户端断开连接时
void qFormTCPServer::onClientDisconnected()
{
    ui->plainTextEdit->appendPlainText("**client socket disconnected");
    tcpSocket->deleteLater();
    //    deleteLater();//QObject::deleteLater();
}

//读取缓冲区行文本
void qFormTCPServer::onSocketReadyRead()
{
//    QStringList   lines;
    while(tcpSocket->canReadLine())
        ui->plainTextEdit->appendPlainText("[in] "+tcpSocket->readLine());
//        lines.append(clientConnection->readLine());
}

//开始监听
void qFormTCPServer::on_actStart_triggered()
{
    QString     IP=ui->comboIP_2->currentText();//IP地址
    quint16     port=ui->spinPort_2->value();//端口
    QHostAddress    addr(IP);
    tcpServer->listen(addr,port);//
//    tcpServer->listen(QHostAddress::LocalHost,port);// Equivalent to QHostAddress("127.0.0.1").
    ui->plainTextEdit->appendPlainText(QStringLiteral("**开始监听..."));
    ui->plainTextEdit->appendPlainText(QStringLiteral("**服务器地址：")
                       +tcpServer->serverAddress().toString());
    ui->plainTextEdit->appendPlainText(QStringLiteral("**服务器端口：")
                       +QString::number(tcpServer->serverPort()));

    ui->actStart->setEnabled(false);
    ui->actStop->setEnabled(true);

    LabListen->setText(QStringLiteral("监听状态：正在监听"));
}

//停止监听
void qFormTCPServer::on_actStop_triggered()
{
    if (tcpServer->isListening()) //tcpServer正在监听
    {
        tcpServer->close();//停止监听
        ui->actStart->setEnabled(true);
        ui->actStop->setEnabled(false);
        LabListen->setText(QStringLiteral("监听状态：已停止监听"));
    }
}

void qFormTCPServer::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

//发送一行字符串，以换行符结束
void qFormTCPServer::on_btnSend_2_clicked()
{
    QString  msg=ui->editMsg_2->text();
    ui->plainTextEdit->appendPlainText("[out] "+msg);
    ui->editMsg_2->clear();
    ui->editMsg_2->setFocus();

    QByteArray  str=msg.toUtf8();
    str.append('\n');//添加一个换行符
    tcpSocket->write(str);
}

//获取本机地址
void qFormTCPServer::on_actHostInfo_triggered()
{
    QString hostName=QHostInfo::localHostName();//本地主机名
    ui->plainTextEdit->appendPlainText(QStringLiteral("本机主机名：")+hostName+"\n");
    QHostInfo   hostInfo=QHostInfo::fromName(hostName);//主机信息

    QList<QHostAddress> addList=hostInfo.addresses();//IP地址列表
    if (!addList.isEmpty())
    for (int i=0;i<addList.count();i++)
    {
        QHostAddress aHost=addList.at(i);
        if (QAbstractSocket::IPv4Protocol==aHost.protocol())//protocal当前的协议类型
        {
            QString IP=aHost.toString();
            ui->plainTextEdit->appendPlainText(QStringLiteral("本机IP地址：")+aHost.toString());
            if (ui->comboIP_2->findText(IP)<0)
                ui->comboIP_2->addItem(IP);
        }
    }
}

