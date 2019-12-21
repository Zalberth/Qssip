#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <iostream>
#include <QDebug>
#include "logindlg.h"
#include "regdlg.h"
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
    void hideLoginDlg();
    void showRegDlg();

private:
    Ui::MainWindow *ui;
    LoginDlg loginDlg;
    RegDlg regDlg;
    bool isLogin;
};
#endif // MAINWINDOW_H
