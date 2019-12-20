#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionLogin->setShortcut(QKeySequence("Command + L"));
    connect(ui->actionLogin, &QAction::triggered, this, &MainWindow::sendLoginReq);
    connect(&loginDlg, &LoginDlg::loginSuccess, this, &MainWindow::hideLoginDlg);

    isLogin = false;
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendBtn_clicked(bool checked)
{
    Q_UNUSED(checked)
    // process text to be sent
    ui->msgListBox->setText(ui->textSendingBox->toPlainText());
    // get current time
    QString msgTime = QString::number(QDateTime::currentDateTime().toTime_t());
    cout << msgTime.toStdString() << endl;

}


void MainWindow::sendLoginReq()
{
    qDebug() << "isLogin:" << isLogin;
    if(isLogin == false)
    {
        // show login dialog
        // 禁止与其它窗口交互
        loginDlg.setWindowModality(Qt::ApplicationModal);
        // TODO: 禁止最大化最小化，Mac下暂时无效
        loginDlg.setWindowFlags(loginDlg.windowFlags()&~Qt::WindowMaximizeButtonHint);
        // 固定窗体大小
        loginDlg.setFixedSize(loginDlg.width(), loginDlg.height());
        // 显示窗口
        loginDlg.show();
    }
}

void MainWindow::hideLoginDlg()
{
    loginDlg.hide();
    isLogin = true;
    this->setWindowTitle("Hello, " + loginDlg.GetCurUser());
    qDebug() << "in HideLoginDlg: isLogin " << isLogin;
}


