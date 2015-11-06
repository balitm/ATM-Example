/****************************************************************************
** Meta object code from reading C++ file 'atmdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "atmdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'atmdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ATMDialog_t {
    QByteArrayData data[11];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ATMDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ATMDialog_t qt_meta_stringdata_ATMDialog = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ATMDialog"
QT_MOC_LITERAL(1, 10, 23), // "on_enter1Button_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 25), // "on_cardIdEdit_textChanged"
QT_MOC_LITERAL(4, 61, 4), // "arg1"
QT_MOC_LITERAL(5, 66, 22), // "on_pinEdit_textChanged"
QT_MOC_LITERAL(6, 89, 23), // "on_enter2Button_clicked"
QT_MOC_LITERAL(7, 113, 25), // "on_newPinEdit_textChanged"
QT_MOC_LITERAL(8, 139, 27), // "on_pinEnteredButton_clicked"
QT_MOC_LITERAL(9, 167, 33), // "on_cashWithdrawalOkButton_cli..."
QT_MOC_LITERAL(10, 201, 30) // "on_ballanceCheckButton_clicked"

    },
    "ATMDialog\0on_enter1Button_clicked\0\0"
    "on_cardIdEdit_textChanged\0arg1\0"
    "on_pinEdit_textChanged\0on_enter2Button_clicked\0"
    "on_newPinEdit_textChanged\0"
    "on_pinEnteredButton_clicked\0"
    "on_cashWithdrawalOkButton_clicked\0"
    "on_ballanceCheckButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ATMDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    1,   55,    2, 0x08 /* Private */,
       5,    1,   58,    2, 0x08 /* Private */,
       6,    0,   61,    2, 0x08 /* Private */,
       7,    1,   62,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ATMDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ATMDialog *_t = static_cast<ATMDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_enter1Button_clicked(); break;
        case 1: _t->on_cardIdEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_pinEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_enter2Button_clicked(); break;
        case 4: _t->on_newPinEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_pinEnteredButton_clicked(); break;
        case 6: _t->on_cashWithdrawalOkButton_clicked(); break;
        case 7: _t->on_ballanceCheckButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject ATMDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ATMDialog.data,
      qt_meta_data_ATMDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ATMDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ATMDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ATMDialog.stringdata0))
        return static_cast<void*>(const_cast< ATMDialog*>(this));
    if (!strcmp(_clname, "NetworkDelegate"))
        return static_cast< NetworkDelegate*>(const_cast< ATMDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ATMDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
