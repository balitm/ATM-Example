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

#include "cardmodel.h"
#include <assert.h>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>

const QString CardModel::kKeyCard(QStringLiteral("Card"));
const QString CardModel::kKeyPIN(QStringLiteral("PIN"));
const QString CardModel::kKeyURL(QStringLiteral("Url"));
const QString CardModel::kKeyBallance(QStringLiteral("Ballance"));

static const QString filePath(QDir::homePath() + QStringLiteral("/.cardinfo"));


CardModel::CardModel()
{
    QFile loadFile(filePath);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open %s file.", filePath.toUtf8().constData());
    }

    QByteArray cardData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(cardData));
    assert(loadDoc.isObject());
    _object = loadDoc.object();
    qDebug() << "card: " << cardId() << ", PIN: " << pinNumString() << '\n';
}


void CardModel::save()
{
    QFile saveFile(filePath);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open %s file.", filePath.toUtf8().constData());
    }
    QJsonDocument doc(_object);
    saveFile.write(doc.toJson());
}


void CardModel::setBallanceSlot(int ballance)
{
    setBallance(ballance);
}