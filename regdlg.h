#ifndef REGDLG_H
#define REGDLG_H

#include <QWidget>
#include <QtNetwork>
#include <QRegExp>
#include <QRegExpValidator>
namespace Ui {
class RegDlg;
}

class RegDlg : public QWidget
{
    Q_OBJECT

public:
    explicit RegDlg(QWidget *parent = nullptr);
    ~RegDlg();

private slots:
    void on_pushButtonConfirm_clicked();
    bool checkReg();
    void requestFinished(QNetworkReply *reply);

private:
    Ui::RegDlg *ui;

    void postRegData();

};

#endif // REGDLG_H
