/**********************************
 * TCP客户端功能代码
 * 20190508
 * *******************************/
#include "qformtcp.h"
#include "ui_qformtcp.h"

#include    <QToolBar>
#include    <QFileInfo>
#include    <QHostAddress>
#include    <QHostInfo>

#include    <picremainwindow.h>

//获得本机IP
QString qFormTCP::getLocalIP()
{
    QString hostName=QHostInfo::localHostName();//本地主机名
    QHostInfo   hostInfo=QHostInfo::fromName(hostName);//主机信息
    QString   localIP="";

    QList<QHostAddress> addList=hostInfo.addresses();//IP地址列表

    if (!addList.isEmpty())
    for (int i=0;i<addList.count();i++)
    {
        QHostAddress aHost=addList.at(i);
        if (QAbstractSocket::IPv4Protocol==aHost.protocol())//protocal当前的协议类型
        {
            localIP=aHost.toString();
            break;
        }
    }
    return localIP;
}

//窗口右上角关闭按钮对应事件
void qFormTCP::closeEvent(QCloseEvent *event)
{
    if (tcpClient->state()==QAbstractSocket::ConnectedState)
        tcpClient->disconnectFromHost();
    event->accept();
}

qFormTCP::qFormTCP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qFormTCP)
{
    ui->setupUi(this);

    //使用UI设计的Actions设计工具栏
    QToolBar* locToolBar = new QToolBar(tr("文档"),this); //创建工具栏
    locToolBar->addAction(ui->actConnect);
    locToolBar->addAction(ui->actDisconnect);
    locToolBar->addAction(ui->actClear);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->actQuit);

    locToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //socket相关
    tcpClient=new QTcpSocket(this); //创建socket变量

    //状态栏标签，暂不用
    //LabSocketState=new QLabel("Socket状态：");//状态栏标签
    //LabSocketState->setMinimumWidth(250);
    //ui->statusBar->addWidget(LabSocketState);

    QString localIP=getLocalIP();//本机IP
    //QStringLiteral()可以解决中文乱码
    this->setWindowTitle(this->windowTitle()+QStringLiteral("----本机IP：")+localIP);
    ui->comboServer->addItem(localIP);


    connect(tcpClient,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(tcpClient,SIGNAL(disconnected()),this,SLOT(onDisconnected()));

    connect(tcpClient,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this,SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
    connect(tcpClient,SIGNAL(readyRead()),
            this,SLOT(onSocketReadyRead()));
#if 0
    QVBoxLayout *Layout = new QVBoxLayout();
    Layout->addWidget(locToolBar); //设置工具栏和编辑器上下布局
    Layout->addWidget(ui->tcpMenu);
    Layout->setContentsMargins(2,2,2,2); //减小边框的宽度
    //Layout->setSpacing(2);
    this->setLayout(Layout); //设置布局
#endif
}

qFormTCP::~qFormTCP()
{
    delete ui;
}

//connected()信号槽函数
void qFormTCP::onConnected()
{
    ui->plainTextEdit->appendPlainText(QStringLiteral("**已连接到服务器"));
    ui->plainTextEdit->appendPlainText("**peer address:"+
                                   tcpClient->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**peer port:"+
                                   QString::number(tcpClient->peerPort()));
    ui->actConnect->setEnabled(false);
    ui->actDisconnect->setEnabled(true);
}

//disConnected()信号槽函数
void qFormTCP::onDisconnected()
{
    ui->plainTextEdit->appendPlainText(QStringLiteral("**已断开与服务器的连接"));
    ui->actConnect->setEnabled(true);
    ui->actDisconnect->setEnabled(false);
}

//readyRead()信号槽函数
void qFormTCP::onSocketReadyRead()
{
    while(tcpClient->canReadLine())
        ui->plainTextEdit->appendPlainText("[in] "+tcpClient->readLine());
}

//stateChange()信号槽函数
void qFormTCP::onSocketStateChange(QAbstractSocket::SocketState socketState)
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

//连接到服务器
void qFormTCP::on_actConnect_triggered()
{
    QString     addr=ui->comboServer->currentText();
    quint16     port=ui->spinPort->value();
    tcpClient->connectToHost(addr,port);
//    tcpClient->connectToHost(QHostAddress::LocalHost,port);
}

//断开与服务器的连接
void qFormTCP::on_actDisconnect_triggered()
{
    if (tcpClient->state()==QAbstractSocket::ConnectedState)
        tcpClient->disconnectFromHost();
}

//清除字符显示区的文字
void qFormTCP::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

//发送数据
void qFormTCP::on_btnSend_clicked()
{
    QString  msg=ui->editMsg->text();
    ui->plainTextEdit->appendPlainText("[out] "+msg);
    ui->editMsg->clear();
    //setFocus()对于输入的消息框启动该功能
    ui->editMsg->setFocus();

    QByteArray  str=msg.toUtf8();
    str.append('\n');
    tcpClient->write(str);
}
