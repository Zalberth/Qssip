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

    QString GetCurUser();

private slots:
    void on_pushButton_clicked();
    void requestFinished(QNetworkReply *reply);

    void on_pushButtonReg_clicked();

signals:
    void loginSuccess(); // 成功登录
    void regEvent();
private:
    Ui::LoginDlg *ui;
    QString curUser;
};

#endif // LOGINDLG_H
