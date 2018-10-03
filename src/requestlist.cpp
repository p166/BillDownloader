#include "requestlist.h"

RequestList::RequestList(QObject *parent) : QObject(parent)
{
    connect(&nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    timer.setInterval(100);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerRequest()));
}

QString base64(QString data)
{
    QByteArray text;
    text.append(data);
    return text.toBase64();
}

int RequestList::getCountResult(const RECONIZE_RESULT result)
{
    int res = 0;
    for (int i=0; i<model_scan->vector.count(); i++) {
        if (model_scan->vector.at(i).result == result)
            res++;
    }

    return res;
}

void RequestList::run()
{
    int total = getCountResult(NO_RECONIZE);
    if (total>0) {
        emit req_total(total);
        beginRequest();
    }
}

bool RequestList::beginRequest()
{
    for (int i=0; i<model_scan->vector.count(); i++) {
        if (model_scan->vector.at(i).result == NO_RECONIZE) {
            model_scan->vector[i].result = RECONIZE_PROGRESS;
            sendRequest(i);
            timer.start();
            return true;
        }
    }

    return false;
}

//получаем индекс активного запроса
int RequestList::getIndexInProgress()
{
    for (int i=0; i<model_scan->vector.count(); i++) {
        if (model_scan->vector.at(i).result == RECONIZE_PROGRESS) {
            return i;
        }
    }
    return -1;
}

void RequestList::timerRequest()
{
    const int current = getIndexInProgress();
    if (current == -1) {
        if (!beginRequest()) {
            timer.stop();
        }
    }
}

void RequestList::setAuth(const QString user, const QString pass, const QString m_FakeDeviceID)
{
    this->user = user;
    this->pass = pass;
    this->m_FakeDeviceID = m_FakeDeviceID;
}

//установка итоговой модели и модели с распознанными qr
void RequestList::setModels(ModelRecepeits *model_recepeits, ModelScan *model_scan)
{
    this->model_recepeits = model_recepeits;
    this->model_scan = model_scan;
}

//void RequestList::setAutoFilter(AutoFilter *filter)
//{
//    this->filter = filter;
//}

void RequestList::replyFinished(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();
    qDebug() << "response received";

    if (parseReceipt(response)){
        qDebug() << "parseReceipt ok";
    }
    emit req_reconized();
    if (getCountResult(NO_RECONIZE) == 0) {
        emit req_finished();
    }
    reply->deleteLater();
}

void RequestList::sendRequest(const int index)
{
    sendRequest(model_scan->vector.at(index).FN, model_scan->vector.at(index).FD, model_scan->vector.at(index).FPD);
}

void RequestList::sendRequest(const QString fn, const QString fd, const QString fpd)
{
    QUrl url("https://proverkacheka.nalog.ru:9999/v1/inns/*/kkts/*/fss/"+fn+"/tickets/"+fd);

    QUrlQuery query;
    query.addQueryItem("fiscalSign", fpd);
    query.addQueryItem("sendToEmail", "no");

    url.setQuery(query.query());

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Basic "+base64(user+":"+pass)).toUtf8());
    request.setRawHeader("Device-Id", m_FakeDeviceID.toUtf8());
    request.setRawHeader("Device-OS", "Adnroid 5.1");
    request.setRawHeader("Version", "2");
    request.setRawHeader("ClientVersion", "1.4.4.1");

    nam.get(request);
}

bool RequestList::parseReceipt(QByteArray jsonText)
{
    //document
        //receipt
            //items []
                //sum
                //name
                //quantity
            //dateTime
    QJsonDocument doc = QJsonDocument::fromJson(jsonText);

    // check validity of the document
    if(!doc.isNull())
    {
        if (doc.isObject()){
            QJsonValue document = doc.object().value("document");
            if (document.isObject()){
                QJsonValue vreceipt = document.toObject().value("receipt");
                if (vreceipt.isObject()){
                    QJsonObject receipt = vreceipt.toObject();
                    QJsonValue vitems = receipt.value("items");
                    if (vitems.isArray()){
                        QJsonArray items = vitems.toArray();
//                        if (!m_ScanDialog.isAppendToTable()) {
//                            m_Items.clear();
//                        }

                        QDateTime m_ReceiptDateTime;
                        //дата
                        QJsonValue vdateTime = receipt.value("dateTime");
                        if (vdateTime.isString()){
                            m_ReceiptDateTime = QDateTime::fromString(vdateTime.toString(),"yyyy-MM-ddTHH:mm:ss");
                        }

                        //название, адрес магазина, сумма чека
                        {
                            QJsonValue user = receipt.value("user");
                            QJsonValue addr = receipt.value("retailPlaceAddress");
                            QJsonValue totalSum = receipt.value("totalSum");
                            mItem item;
                            item.name = QString("%1 [%2]").arg(user.toString()).arg(addr.toString());
                            item.count = 0;
                            item.price = 0;
                            item.sum = totalSum.toDouble()/100.0;
                            model_recepeits->addRecepiet(item);
                        }

                        //состав чека
                        for (int i =0; i<items.count(); ++i){
                            QJsonValue value = items.at(i);
                            if (value.isObject()){
                                QJsonObject item = value.toObject();
                                QJsonValue sum = item.value("sum");
                                QJsonValue name = item.value("name");
                                QJsonValue quantity = item.value("quantity");
                                if(sum.isDouble() && name.isString() && quantity.isDouble()){
                                    QString eName = name.toString().replace(";","",Qt::CaseInsensitive);
                                    {
                                        mItem item;
                                        item.name = eName;
//                                        item.category = filter->getCategory(item.name);
                                        item.count = quantity.toDouble();
                                        item.price = sum.toDouble()/100.0;
                                        item.date = m_ReceiptDateTime;
                                        if (!item.date.isNull()) {
//                                            item.category = filter->getCategory(item.name);
                                        }
                                        model_recepeits->addRecepiet(item);
                                        qDebug() << "adding" << item.name << item.date.toString("yyyy-MM-ddTHH:mm:ss");
                                    }
                                }
                            }
                        }

                        const int current = getIndexInProgress();
                        if (current!=-1) {
                            model_scan->vector[current].result = RECONIZE_OK;
                            model_scan->forceUpdate();
                        }
                        model_recepeits->forceUpdate();
                        return true;
                    }
                }
            }
        }
    }
    else{
        qWarning() << "not json";

        const int current = getIndexInProgress();
        if (current!=-1) {
            model_scan->vector[current].result = RECONIZE_ERR;
            model_scan->forceUpdate();
        }
    }


    return false;
}
