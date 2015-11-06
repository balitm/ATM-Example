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

#include "atmdialog.h"
#include "ui_atmdialog.h"
#include "cardmodel.h"
#include <QSignalMapper>
#include <QMessageBox>


ATMDialog::ATMDialog(QWidget *parent) :
    QDialog(parent),
    _cardModel(),
    _networkModel(*this),
    ui(new Ui::ATMDialog)
{
    ui->setupUi(this);

    // Changes a bunch of signals into one signal with an index.
    auto mapper = new QSignalMapper(this);

    //---- pin change ----
    mapper->setMapping(ui->pinChangeButton, 4);
    connect(ui->pinChangeButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pinCancelButton, 2);
    connect(ui->pinCancelButton, SIGNAL(clicked()), mapper, SLOT(map()));

    //---- mini statement ----
    mapper->setMapping(ui->statementButton, 3);
    connect(ui->statementButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->statementBackButton, 2);
    connect(ui->statementBackButton, SIGNAL(clicked()), mapper, SLOT(map()));

    //---- ballance check ----
    mapper->setMapping(ui->ballanceBackButton, 2);
    connect(ui->ballanceBackButton, SIGNAL(clicked()), mapper, SLOT(map()));

    //---- cache withdrawal ----
    mapper->setMapping(ui->cashWithdrawalButton, 6);
    connect(ui->cashWithdrawalButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->cashWithdrawalCancelButton, 2);
    connect(ui->cashWithdrawalCancelButton, SIGNAL(clicked()), mapper, SLOT(map()));

    connect(mapper, SIGNAL(mapped(int)), ui->stackedWidget, SLOT(setCurrentIndex(int)));
}


ATMDialog::~ATMDialog()
{
    delete ui;
}


//---- delegate implementation ----

void ATMDialog::getReturned(int ballance)
{
    if (ballance != CardModel::kNotFound) {
        _cardModel.setBallance(ballance);
        emit ui->stackedWidget->setCurrentIndex(2);
    }
}

void ATMDialog::postReturned(int ballance)
{
    if (ballance != CardModel::kNotFound) {
        qDebug() << "New ballance after withdrawal: " << ballance << '\n';
        _cardModel.setBallance(ballance);
        emit ui->stackedWidget->setCurrentIndex(2);
    } else {
        ui->cashWithdrawalLabel->setText(QString("Failed, ballance: %1").arg(_cardModel.ballance()));
    }
}


//---- Qt Slots ----

void ATMDialog::on_enter1Button_clicked()
{
    printf("enter1Btn clicked.\n");
    assert(ui->cardIdEdit->text().length() == 4);
    ui->enter2Button->setDefault(true);
    emit ui->stackedWidget->setCurrentIndex(1);
}

void ATMDialog::on_cardIdEdit_textChanged(const QString &arg1)
{
    ui->enter1Button->setEnabled(arg1.length() == 4);
}

void ATMDialog::on_pinEdit_textChanged(const QString &arg1)
{
    ui->enter2Button->setEnabled(arg1.length() == 4);
}

void ATMDialog::on_enter2Button_clicked()
{
    assert(ui->cardIdEdit->text().length() == 4);
    if (ui->pinEdit->text() == _cardModel.pinNumString()) {
        _networkModel.getBallance(_cardModel.urlString(), _cardModel.cardId());
    } else {
        QMessageBox msgBox(QMessageBox::Warning, "Error", "Wrong pin code!",
                           QMessageBox::Ok);
        msgBox.exec();
        ui->pinEdit->clear();
    }
}

void ATMDialog::on_newPinEdit_textChanged(const QString &arg1)
{
    ui->pinEnteredButton->setEnabled(arg1.length() == 4);
}

void ATMDialog::on_pinEnteredButton_clicked()
{
    assert(ui->newPinEdit->text().length() == 4);
    _cardModel.setPinNumString(ui->newPinEdit->text());
    _cardModel.save();
    emit ui->stackedWidget->setCurrentIndex(2);
}

void ATMDialog::on_cashWithdrawalOkButton_clicked()
{
    //---- get the amount ----
    int amount = ui->cashWithdrawalEdit->text().toInt();

    //---- post to server ----
    _networkModel.postCashWithdrawal(_cardModel.urlString(), _cardModel.cardId(), amount);
    ui->cashWithdrawalLabel->setText("Posting request.");
}

void ATMDialog::on_ballanceCheckButton_clicked()
{
    QString str;
    str.setNum(_cardModel.ballance());
    qDebug() << "Setting ballance str to: " << str << '\n';
    ui->ballanceEdit->setText(str);
    ui->stackedWidget->setCurrentIndex(5);
}
