#include "picremainwindow.h"
#include "ui_picremainwindow.h"

#include    <QPainter>
#include    <QFileDialog>

PicReMainWindow::PicReMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PicReMainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();//清除所有页面
    ui->tabWidget->tabsClosable(); //Page有关闭按钮，可被关闭

    this->setCentralWidget(ui->tabWidget);
  //this->setWindowState(Qt::WindowFullScreen); //窗口全屏显示
    this->setWindowState(Qt::WindowMaximized); //窗口最大化显示
  //this->setWindowState(Qt::WindowMinimized); //窗口最小化显示
    this->setAutoFillBackground(true);

  //this->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除

  //Qt::WindowFlags    flags=this->windowFlags();
  //this->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint); //设置对话框固定大小
}

PicReMainWindow::~PicReMainWindow()
{
    delete ui;
}

//绘制窗口背景图片
void PicReMainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);//防止编译器出现unused警告
    QPainter painter(this);
    painter.drawPixmap(0,ui->mainToolBar->height(),this->width(),
                       this->height()-ui->mainToolBar->height()-ui->statusBar->height(),
                       QPixmap(":/images/images/back2.jpg"));
}

//void QWMainWindow::setCurrentTabText(const QString &text)
//{
//    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),text);
//}



//void QWMainWindow::on_actDocument_triggered()
//{ //新建文档窗口
////    QFormDoc    *formDoc;
//    QFormDoc *formDoc = new QFormDoc(); //不指定父窗口，单独用show()方法显示
//    formDoc->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
//    formDoc->setWindowTitle("基于QWidget的窗口，无父窗口，关闭时删除");
//    formDoc->show(); //在单独的窗口中显示

////    int cur=ui->tabWidget->addTab(formDoc,QString::asprintf("Doc %d",ui->tabWidget->count()));
////    ui->tabWidget->setCurrentIndex(cur);
////    ui->tabWidget->setVisible(true);
//}

//关闭Tab
void PicReMainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (index<0)
        return;

//    QFormTable    *fmTable;
//    fmTable= static_cast<QFormTable*>(ui->tabWidget->widget(index));
//    fmTable->close();

//    QFormDoc    *formDoc;
//    formDoc= static_cast<QFormDoc*>(ui->tabWidget->widget(index));
//    formDoc->close();

//    QWidget    *aForm;
//    aForm= static_cast<QWidget*>(ui->tabWidget->widget(index));
    QWidget* aForm=ui->tabWidget->widget(index);
    aForm->close();

//    ui->tabWidget->removeTab(index);
}


//创建QFormDoc窗体，并在tabWidget中显示
void PicReMainWindow::on_actWidgetInsite_triggered()
{
    QFormDoc *formDoc = new QFormDoc(this); //不指定父窗口，单独用show()方法显示
    formDoc->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除

//    formDoc->setWindowFlag(Qt::Widget,true);
//    formDoc->setWindowFlag(Qt::CustomizeWindowHint,true);
//    formDoc->setWindowFlag(Qt::WindowMinMaxButtonsHint,false);

//    formDoc->setWindowState(Qt::WindowMaximized);
//    formDoc->setWindowOpacity(0.5);
//    formDoc->setWindowModality(Qt::WindowModal);

//    formDoc->show(); //在单独的窗口中显示
//    formDoc->setWindowTitle("基于QWidget的窗口，无父窗口，关闭时删除");
    int cur=ui->tabWidget->addTab(formDoc,
            QString::asprintf("Doc %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

#if 0
void PicReMainWindow::on_actWindowInsite_triggered()
{
    QFormTable *formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    //    aTable->setWindowTitle("基于QWidget的窗口，无父窗口，关闭时删除");
    int cur=ui->tabWidget->addTab(formTable,
              QString::asprintf("Table %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}
#endif

//TCP客户端
void PicReMainWindow::on_actTCPClient_triggered()
{
    qFormTCP* formTcp = new qFormTCP(this);
//    formChart = new QFormTable(); //无父窗体,在windows任务栏上有显示
    formTcp->setAttribute(Qt::WA_DeleteOnClose); //对话框关闭时自动删除对话框对象,用于不需要读取返回值的对话框
    formTcp->setWindowTitle(QStringLiteral("TCP客户端"));
//    formChart->setWindowTitle("多实例窗口，指定父窗口");
    formTcp->setWindowFlag(Qt::Window,true);
    formTcp->setWindowOpacity(0.9);
    formTcp->show();
}

//TCP服务端
void PicReMainWindow::on_actTCPServer_triggered()
{
    qFormTCPServer* formTcpServer = new qFormTCPServer(this);
//    formChart = new QFormTable(); //无父窗体,在windows任务栏上有显示
    formTcpServer->setAttribute(Qt::WA_DeleteOnClose); //对话框关闭时自动删除对话框对象,用于不需要读取返回值的对话框
    formTcpServer->setWindowTitle(QStringLiteral("TCP服务端"));
//    formChart->setWindowTitle("多实例窗口，指定父窗口");
    formTcpServer->setWindowFlag(Qt::Window,true);
    formTcpServer->setWindowOpacity(0.9);
    formTcpServer->show();
}


void PicReMainWindow::on_actWidget_triggered()
{
    QFormDoc *formDoc = new QFormDoc(); //不指定父窗口，用show()显示
    formDoc->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    formDoc->setWindowTitle(QStringLiteral("基于QWidget的窗体，无父窗口，关闭时删除"));

    formDoc->setWindowFlag(Qt::Window,true);

//    formDoc->setWindowFlag(Qt::CustomizeWindowHint,true);
//    formDoc->setWindowFlag(Qt::WindowMinMaxButtonsHint,true);
//    formDoc->setWindowFlag(Qt::WindowCloseButtonHint,true);
//    formDoc->setWindowFlag(Qt::WindowStaysOnTopHint,true);

//    formDoc->setWindowState(Qt::WindowMaximized);
    formDoc->setWindowOpacity(0.9);
//    formDoc->setWindowModality(Qt::WindowModal);

    formDoc->show(); //在单独的窗口中显示
}

void PicReMainWindow::on_tabWidget_currentChanged(int index)
{
    bool  en=ui->tabWidget->count()>0; //再无页面时，actions禁用
    ui->tabWidget->setVisible(en);
}
