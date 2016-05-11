/****************************************************************************
** Meta object code from reading C++ file 'ControlView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ControlView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ControlView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ControlView_t {
    QByteArrayData data[15];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlView_t qt_meta_stringdata_ControlView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ControlView"
QT_MOC_LITERAL(1, 12, 13), // "sendMsgToMain"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "sendStartToBoard"
QT_MOC_LITERAL(4, 44, 15), // "sendStartToMain"
QT_MOC_LITERAL(5, 60, 14), // "sendDrawToMain"
QT_MOC_LITERAL(6, 75, 14), // "sendUndoToMain"
QT_MOC_LITERAL(7, 90, 15), // "sendLeaveToMain"
QT_MOC_LITERAL(8, 106, 7), // "sendMsg"
QT_MOC_LITERAL(9, 114, 7), // "readMsg"
QT_MOC_LITERAL(10, 122, 5), // "block"
QT_MOC_LITERAL(11, 128, 5), // "start"
QT_MOC_LITERAL(12, 134, 4), // "draw"
QT_MOC_LITERAL(13, 139, 4), // "undo"
QT_MOC_LITERAL(14, 144, 5) // "leave"

    },
    "ControlView\0sendMsgToMain\0\0sendStartToBoard\0"
    "sendStartToMain\0sendDrawToMain\0"
    "sendUndoToMain\0sendLeaveToMain\0sendMsg\0"
    "readMsg\0block\0start\0draw\0undo\0leave"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       3,    0,   77,    2, 0x06 /* Public */,
       4,    1,   78,    2, 0x06 /* Public */,
       5,    1,   81,    2, 0x06 /* Public */,
       6,    1,   84,    2, 0x06 /* Public */,
       7,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   90,    2, 0x0a /* Public */,
       9,    1,   91,    2, 0x0a /* Public */,
      11,    0,   94,    2, 0x0a /* Public */,
      12,    0,   95,    2, 0x0a /* Public */,
      13,    0,   96,    2, 0x0a /* Public */,
      14,    0,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ControlView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ControlView *_t = static_cast<ControlView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMsgToMain((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->sendStartToBoard(); break;
        case 2: _t->sendStartToMain((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->sendDrawToMain((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->sendUndoToMain((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->sendLeaveToMain((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 6: _t->sendMsg(); break;
        case 7: _t->readMsg((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->start(); break;
        case 9: _t->draw(); break;
        case 10: _t->undo(); break;
        case 11: _t->leave(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ControlView::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlView::sendMsgToMain)) {
                *result = 0;
            }
        }
        {
            typedef void (ControlView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlView::sendStartToBoard)) {
                *result = 1;
            }
        }
        {
            typedef void (ControlView::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlView::sendStartToMain)) {
                *result = 2;
            }
        }
        {
            typedef void (ControlView::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlView::sendDrawToMain)) {
                *result = 3;
            }
        }
        {
            typedef void (ControlView::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlView::sendUndoToMain)) {
                *result = 4;
            }
        }
        {
            typedef void (ControlView::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlView::sendLeaveToMain)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject ControlView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ControlView.data,
      qt_meta_data_ControlView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ControlView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ControlView.stringdata0))
        return static_cast<void*>(const_cast< ControlView*>(this));
    return QWidget::qt_metacast(_clname);
}

int ControlView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ControlView::sendMsgToMain(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ControlView::sendStartToBoard()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ControlView::sendStartToMain(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ControlView::sendDrawToMain(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ControlView::sendUndoToMain(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ControlView::sendLeaveToMain(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
