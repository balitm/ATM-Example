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

#ifndef NETWORKMODEL_H
#define NETWORKMODEL_H

#include <QNetworkAccessManager>
#include <QString>

class ATMDialog;
class CardModel;

class NetworkDelegate
{
public:
    virtual void getReturned(int ballance) = 0;
    virtual void postReturned(int ballance) = 0;
};


class NetworkModel : public QObject
{
    Q_OBJECT

public:
    explicit NetworkModel(NetworkDelegate &delegate);

    // Http get the ballance of the given card.
    void getBallance(const QString &uriString, const QString &cardId);

    // Http post JSon data containing the withdrawal amount and picture.
    void postCashWithdrawal(const QString &uriString, const QString &cardId, int amount);

private slots:
    // Handle network operation finished event.
    void _handleNetworkData(QNetworkReply* reply);

    void _sslErrors(QNetworkReply * reply, const QList<QSslError> & errors);

private:
    enum State {
        kNone,
        kGetPending,
        kPostPending
    };

    NetworkDelegate &_delegate;
    QNetworkAccessManager _networkManager;
    State _state = State::kNone;
};

#endif // NETWORKMODEL_H
