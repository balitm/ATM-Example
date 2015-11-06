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

#ifndef ATMDIALOG_H
#define ATMDIALOG_H

#include <QDialog>
#include "networkmodel.h"
#include "cardmodel.h"


namespace Ui {
class ATMDialog;
}

class ATMDialog : public QDialog, NetworkDelegate
{
    Q_OBJECT

public:
    ATMDialog(QWidget *parent = 0);
    virtual ~ATMDialog();

    virtual void getReturned(int ballance) override;
    virtual void postReturned(int ballance) override;


private slots:
    void on_enter1Button_clicked();

    void on_cardIdEdit_textChanged(const QString &arg1);

    void on_pinEdit_textChanged(const QString &arg1);

    void on_enter2Button_clicked();

    void on_newPinEdit_textChanged(const QString &arg1);

    void on_pinEnteredButton_clicked();

    void on_cashWithdrawalOkButton_clicked();

    void on_ballanceCheckButton_clicked();

private:
    CardModel _cardModel;
    NetworkModel _networkModel;
    Ui::ATMDialog *ui;
};

#endif // ATMDIALOG_H
