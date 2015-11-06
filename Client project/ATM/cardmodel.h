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

#ifndef CARDMODEL_H
#define CARDMODEL_H

#include <assert.h>
#include <QJsonObject>
#include <QObject>


class CardModel : public QObject
{
    Q_OBJECT

public:
    static const QString kKeyCard;
    static const QString kKeyPIN;
    static const QString kKeyURL;
    static const QString kKeyBallance;
    static const int kNotFound = -1;


    CardModel();

    const QString cardId() const {
        assert(_object[kKeyCard].isString());
        return _object[kKeyCard].toString();
    }

    const QString pinNumString() const {
        assert(_object[kKeyPIN].isString());
        return _object[kKeyPIN].toString();
    }

    void setPinNumString(const QString &pin) {
        _object[kKeyPIN] = pin;
    }

    const QString urlString() const {
        assert(_object[kKeyURL].isString());
        return _object[kKeyURL].toString();
    }

    int ballance() const {
//        assert(_object[kKeyBallance].isInt());
        return _object[kKeyBallance].toInt();
    }

    void setBallance(int ballance) {
        _object[kKeyBallance] = ballance;
    }

    void save();

private slots:
    void setBallanceSlot(int ballance);

private:
    QJsonObject _object;
};

#endif // CARDMODEL_H
