#include "logindlg.h"
#include "ui_logindlg.h"

LoginDlg::LoginDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_pushButton_clicked()
{
    // send network request
    QNetworkRequest req;
    QNetworkAccessManager* nm = new QNetworkAccessManager(this);
    QMetaObject::Connection connRet = QObject::connect(nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);

    QString loginUrl = "http://localhost:8080/login";

    QByteArray postArray;
    postArray.append("username=" + ui->lineEditUsername->text());
    postArray.append("&pwd=" + ui->lineEditPwd->text());

    req.setUrl(QUrl(loginUrl));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentLengthHeader, postArray.size());

    nm->post(req,postArray);
}

void LoginDlg::requestFinished(QNetworkReply *reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
    if(statusCode.isValid())
    {
        qDebug() << "status code = " << statusCode.toInt();
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
    } else {
//        qDebug() << "hi:" + reply->readAll();
        QByteArray tmp = reply->readAll();
        QJsonParseError jsonpe;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(tmp, &jsonpe);
        if(jsonpe.error == QJsonParseError::NoError)
        {
            if(jsonDoc.isObject())
            {
                QJsonObject obj = jsonDoc.object();
                if(obj.contains("found"))
                {
                    int found = obj["found"].toVariant().toInt();
                    qDebug() << "found:" << found;
                    if(found == 1)
                    {
                        // 登录成功了
                        emit loginSuccess();
                    }
                }
            }
        }
    }
}
