#ifndef REQUESTLIST_H
#define REQUESTLIST_H

#include <QWidget>
#include <QObject>
#include <QVector>
#include <QNetworkReply>
#include <QByteArray>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QCompleter>
#include <QTimer>
#include "cnetclient.h"

#include "utils.h"
#include "modelscan.h"
#include "modelreceipts.h"

class RequestManager : public QObject
{
    Q_OBJECT
public:
    explicit RequestManager(QObject *parent = nullptr);


signals:
    void req_total(int count);
    void req_reconized(bool result);
    void req_finished();

public slots:
    void run();
    void setAuth(const QString user, const QString pass, const QString m_FakeDeviceID);
    void setModels(ModelRecepeits *model_recepeits, ModelScan *model_scan);

private slots:
    bool beginRequest();
    int  getCountResult(const RECONIZE_RESULT result);
    void replyFinished(QNetworkReply *reply);
    void sendRequest(const int index);
    void sendRequest(const QString fn, const QString fd, const QString fpd);
    bool parseReceipt(QByteArray jsonText);
    void timerRequest();
    int  getIndexInProgress();

private:
    QNetworkAccessManager nam;
    QString user;
    QString pass;
    QString m_FakeDeviceID;
    ModelRecepeits *model_recepeits;
    ModelScan *model_scan;
    QTimer  timer;



};

#endif // REQUESTLIST_H
