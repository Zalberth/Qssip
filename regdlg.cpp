#include "regdlg.h"
#include "ui_regdlg.h"

RegDlg::RegDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegDlg)
{
    ui->setupUi(this);
    // regex only: numbers and characters
    QRegExp regx3("^[A-Za-z0-9]+$");
    QValidator *validator = new QRegExpValidator(regx3,ui->lineEditUsername);
    ui->lineEditUsername->setValidator(validator);

    // regex only: numbers, characters and underscore
    QRegExp regx8("^\\w+$");
    QValidator *validator1 = new QRegExpValidator(regx8,ui->lineEditPwd);
    ui->lineEditPwd->setValidator(validator1);
    QValidator *validator2 = new QRegExpValidator(regx8,ui->lineEditPwdConfirm);
    ui->lineEditPwdConfirm->setValidator(validator2);
}

RegDlg::~RegDlg()
{
    delete ui;
}

void RegDlg::on_pushButtonConfirm_clicked()
{
    if(checkReg())
    {
        ui->labelTip->clear();
        // post data and wait for confirm, close reg dialog finally
        postRegData();
    }
}



bool RegDlg::checkReg()
{
    QString uname = ui->lineEditUsername->text();
    QString pwd = ui->lineEditPwd->text();
    QString pwdCf = ui->lineEditPwdConfirm->text();

    if(0 == uname.size())
    {
        ui->labelTip->setText("Username cannot be empty.");
        ui->labelTip->setStyleSheet("color: rgb(255, 78, 25);");
        return false;
    }

    if(uname.size() > 21)
    {
        ui->labelTip->setText("Length of username is over 21 !");
        ui->labelTip->setStyleSheet("color: rgb(255, 78, 25);");
        return false;
    }

    if(pwd.isEmpty())
    {
        ui->labelTip->setText("Password cannot be empty !");
        ui->labelTip->setStyleSheet("color: rgb(255, 78, 25);");
        return false;
    }

    if(pwd.size() < 6 || pwd.size() > 18)
    {
        ui->labelTip->setText("Length of password must be in range [6,18] !");
        ui->labelTip->setStyleSheet("color: rgb(255, 78, 25);");
        return false;
    }

    if(pwdCf.isEmpty())
    {
        ui->labelTip->setText("Please confirm password !");
        ui->labelTip->setStyleSheet("color: rgb(255, 78, 25);");
        return false;
    }

    if(0 != pwd.compare(pwdCf))
    {
        ui->labelTip->setText("Two input password must be consistent.");
        ui->labelTip->setStyleSheet("color: rgb(255, 78, 25);");
        return false;
    }

    return true;
}

void RegDlg::postRegData()
{
    // send network request
    QNetworkRequest req;
    QNetworkAccessManager* nm = new QNetworkAccessManager(this);
    QMetaObject::Connection connRet = QObject::connect(nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);

    QString loginUrl = "http://localhost:8080/register";

    QByteArray postArray;
    postArray.append("username=" + ui->lineEditUsername->text());
    postArray.append("&pwd=" + ui->lineEditPwd->text());

    req.setUrl(QUrl(loginUrl));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentLengthHeader, postArray.size());

    nm->post(req,postArray);
}

void RegDlg::requestFinished(QNetworkReply *reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
    if(statusCode.isValid())
    {
        qDebug() << "status code = " << statusCode.toInt();
        ui->labelTip->setText("fail to register ...");
    }
    // 解析返回的JSON
    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
    {
        qDebug() << "reason = " << reason.toString();
    }
    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError)
    {
        qDebug() << "error !" << reply->errorString();
        ui->labelTip->setText("fail to register ...");
    } else {
        QByteArray tmp = reply->readAll();
        QJsonParseError jsonpe;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(tmp, &jsonpe);
        if(jsonpe.error == QJsonParseError::NoError)
        {
            if(jsonDoc.isObject())
            {
                QJsonObject obj = jsonDoc.object();
                if(obj.contains("success"))
                {
                    int succ = obj["success"].toVariant().toInt();
                    qDebug() << "success:" << succ;
                    if(succ == 0)
                    {
                        this->hide();
                        ui->labelTip->clear();
                    } else {
                        ui->labelTip->setText("fail to register ...");
                    }
                }
            }
        }
    }
}
