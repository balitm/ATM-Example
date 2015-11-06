/*
Copyright (c) 2015 Balazs Kilvady

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "networkmodel.h"
#include "atmdialog.h"
#include "cardmodel.h"
#include <assert.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QNetworkRequest>
#include <QNetworkReply>


static QString kKeyBallance = "ballance";
static QString kKeyAmount = "amount";
static QString kKeyPicture = "picture";


NetworkModel::NetworkModel(NetworkDelegate &delegate) : _delegate(delegate)
{
    connect(&_networkManager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(_handleNetworkData(QNetworkReply *)));
    connect(&_networkManager, SIGNAL(sslErrors(QNetworkReply *, const QList<QSslError> &)),
            this, SLOT(_sslErrors(QNetworkReply *, const QList<QSslError> &)));
}


void NetworkModel::getBallance(const QString &uriString, const QString &cardId)
{
    _state = kGetPending;
    _networkManager.get(QNetworkRequest(uriString + cardId));
}


void NetworkModel::postCashWithdrawal(const QString &uriString, const QString &cardId, int amount)
{
    QJsonObject object;
    object[kKeyAmount] = amount;
    object[kKeyPicture] = QString(30 * 1024, '\0');
    QJsonDocument doc(object);

    QByteArray jsonString = doc.toJson();
    QByteArray length = QByteArray::number(jsonString.size());
    QNetworkRequest request(uriString + cardId);

    //---- add request header ----
    request.setRawHeader("User-Agent", "ATM v0.1");
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", length);

    _state = kPostPending;
    _networkManager.post(request, jsonString);
}


void NetworkModel::_handleNetworkData(QNetworkReply *networkReply)
{
    QByteArray response(networkReply->readAll());
    QJsonDocument doc(QJsonDocument::fromJson(response));
    assert(doc.isObject());
    int ballance = doc.object()[kKeyBallance].toInt();
    qDebug() << "ballance: " << ballance << '\n';

    if (!networkReply->error()) {
        switch (_state) {
            case kGetPending:
                _delegate.getReturned(ballance);
                break;
            case kPostPending:
                _delegate.postReturned(ballance);
                break;
                
            default:
                assert(false);
                break;
        }
    }

    _state = kNone;
    networkReply->deleteLater();
}

void NetworkModel::_sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    reply->ignoreSslErrors(errors);
}
