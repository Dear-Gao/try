/****************************************************************************
** Meta object code from reading C++ file 'kdswidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "kdswidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kdswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KDSWidget_t {
    QByteArrayData data[13];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KDSWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KDSWidget_t qt_meta_stringdata_KDSWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "KDSWidget"
QT_MOC_LITERAL(1, 10, 14), // "tellBtnClicked"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 2), // "id"
QT_MOC_LITERAL(4, 29, 20), // "msgReceiveAnotherOne"
QT_MOC_LITERAL(5, 50, 3), // "msg"
QT_MOC_LITERAL(6, 54, 18), // "nextSelectedOption"
QT_MOC_LITERAL(7, 73, 18), // "lastSelectedOption"
QT_MOC_LITERAL(8, 92, 20), // "confirmCurrentOption"
QT_MOC_LITERAL(9, 113, 18), // "receiveButtonClick"
QT_MOC_LITERAL(10, 132, 1), // "x"
QT_MOC_LITERAL(11, 134, 1), // "y"
QT_MOC_LITERAL(12, 136, 8) // "closeApp"

    },
    "KDSWidget\0tellBtnClicked\0\0id\0"
    "msgReceiveAnotherOne\0msg\0nextSelectedOption\0"
    "lastSelectedOption\0confirmCurrentOption\0"
    "receiveButtonClick\0x\0y\0closeApp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KDSWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   52,    2, 0x0a /* Public */,
       6,    0,   55,    2, 0x08 /* Private */,
       7,    0,   56,    2, 0x08 /* Private */,
       8,    0,   57,    2, 0x08 /* Private */,
       9,    2,   58,    2, 0x08 /* Private */,
      12,    0,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void,

       0        // eod
};

void KDSWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KDSWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tellBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->msgReceiveAnotherOne((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->nextSelectedOption(); break;
        case 3: _t->lastSelectedOption(); break;
        case 4: _t->confirmCurrentOption(); break;
        case 5: _t->receiveButtonClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->closeApp(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (KDSWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KDSWidget::tellBtnClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject KDSWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_KDSWidget.data,
    qt_meta_data_KDSWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KDSWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KDSWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KDSWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int KDSWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void KDSWidget::tellBtnClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
