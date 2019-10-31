#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
