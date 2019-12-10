#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionLogin->setShortcut(QKeySequence("Command+L"));
    connect(ui->actionLogin, &QAction::triggered, this, &MainWindow::sendLoginReq);
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
    cout << "hello user!!" << endl;
    // send network request
    QNetworkRequest req;
    QNetworkAccessManager* nm = new QNetworkAccessManager(this);
    QMetaObject::Connection connRet = QObject::connect(nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);

        req.setUrl(QUrl("http://localhost:1323"));
        QNetworkReply* reply = nm->get(req);
}

void MainWindow::requestFinished(QNetworkReply *reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
    if(statusCode.isValid())
    {
        qDebug() << "status code = " << statusCode.toInt();
    }
    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
    {
        qDebug() << "reason=" << reason.toString();
    }
    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError)
    {
        qDebug() << "error !" << reply->errorString();
    } else {
        qDebug() << reply->readAll();
    }
}
