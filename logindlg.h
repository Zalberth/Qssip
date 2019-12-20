#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QWidget
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = nullptr);
    ~LoginDlg();

private slots:
    void on_pushButton_clicked();
    void requestFinished(QNetworkReply *reply);

signals:
    void loginSuccess(); // 成功登录

private:
    Ui::LoginDlg *ui;
};

#endif // LOGINDLG_H
