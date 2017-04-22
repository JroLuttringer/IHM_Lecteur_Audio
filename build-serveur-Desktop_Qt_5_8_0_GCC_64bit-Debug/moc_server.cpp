/****************************************************************************
** Meta object code from reading C++ file 'server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serveur/server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_server_t {
    QByteArrayData data[10];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_server_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_server_t qt_meta_stringdata_server = {
    {
QT_MOC_LITERAL(0, 0, 6), // "server"
QT_MOC_LITERAL(1, 7, 16), // "signalFromServer"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 10), // "signalType"
QT_MOC_LITERAL(4, 36, 7), // "message"
QT_MOC_LITERAL(5, 44, 5), // "ui_on"
QT_MOC_LITERAL(6, 50, 20), // "connectionFromClient"
QT_MOC_LITERAL(7, 71, 18), // "clientDisconnected"
QT_MOC_LITERAL(8, 90, 9), // "pause_mpv"
QT_MOC_LITERAL(9, 100, 8) // "play_mpv"

    },
    "server\0signalFromServer\0\0signalType\0"
    "message\0ui_on\0connectionFromClient\0"
    "clientDisconnected\0pause_mpv\0play_mpv"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_server[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   54,    2, 0x0a /* Public */,
       5,    0,   59,    2, 0x0a /* Public */,
       6,    0,   60,    2, 0x0a /* Public */,
       7,    0,   61,    2, 0x0a /* Public */,
       8,    0,   62,    2, 0x0a /* Public */,
       9,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QVariantMap,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QVariantMap,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        server *_t = static_cast<server *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalFromServer((*reinterpret_cast< signalType(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        case 1: _t->message((*reinterpret_cast< signalType(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        case 2: _t->ui_on(); break;
        case 3: _t->connectionFromClient(); break;
        case 4: _t->clientDisconnected(); break;
        case 5: _t->pause_mpv(); break;
        case 6: _t->play_mpv(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (server::*_t)(signalType , QVariantMap );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&server::signalFromServer)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject server::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_server.data,
      qt_meta_data_server,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *server::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_server.stringdata0))
        return static_cast<void*>(const_cast< server*>(this));
    return QObject::qt_metacast(_clname);
}

int server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void server::signalFromServer(signalType _t1, QVariantMap _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
