#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QtNetwork>
#include <iostream>
#include <QDebug>
#include "logindlg.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendBtn_clicked(bool checked);
    void sendLoginReq();
    void requestFinished(QNetworkReply* reply);

private:
    Ui::MainWindow *ui;
    LoginDlg loginDlg;
};
#endif // MAINWINDOW_H
