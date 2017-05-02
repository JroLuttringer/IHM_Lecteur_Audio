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
    QByteArrayData data[19];
    char stringdata0[230];
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
QT_MOC_LITERAL(6, 50, 12), // "send_startup"
QT_MOC_LITERAL(7, 63, 20), // "connectionFromClient"
QT_MOC_LITERAL(8, 84, 18), // "clientDisconnected"
QT_MOC_LITERAL(9, 103, 12), // "set_time_mpv"
QT_MOC_LITERAL(10, 116, 9), // "pause_mpv"
QT_MOC_LITERAL(11, 126, 8), // "play_mpv"
QT_MOC_LITERAL(12, 135, 13), // "get_file_name"
QT_MOC_LITERAL(13, 149, 12), // "get_duration"
QT_MOC_LITERAL(14, 162, 10), // "get_volume"
QT_MOC_LITERAL(15, 173, 8), // "get_time"
QT_MOC_LITERAL(16, 182, 13), // "setVolume_mpv"
QT_MOC_LITERAL(17, 196, 13), // "load_file_mpv"
QT_MOC_LITERAL(18, 210, 19) // "send_tree_from_file"

    },
    "server\0signalFromServer\0\0signalType\0"
    "message\0ui_on\0send_startup\0"
    "connectionFromClient\0clientDisconnected\0"
    "set_time_mpv\0pause_mpv\0play_mpv\0"
    "get_file_name\0get_duration\0get_volume\0"
    "get_time\0setVolume_mpv\0load_file_mpv\0"
    "send_tree_from_file"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_server[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   99,    2, 0x0a /* Public */,
       5,    0,  104,    2, 0x0a /* Public */,
       6,    0,  105,    2, 0x0a /* Public */,
       7,    0,  106,    2, 0x0a /* Public */,
       8,    0,  107,    2, 0x0a /* Public */,
       9,    1,  108,    2, 0x0a /* Public */,
      10,    0,  111,    2, 0x0a /* Public */,
      11,    0,  112,    2, 0x0a /* Public */,
      12,    0,  113,    2, 0x0a /* Public */,
      13,    0,  114,    2, 0x0a /* Public */,
      14,    0,  115,    2, 0x0a /* Public */,
      15,    0,  116,    2, 0x0a /* Public */,
      16,    1,  117,    2, 0x0a /* Public */,
      17,    1,  120,    2, 0x0a /* Public */,
      18,    0,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QVariantMap,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QVariantMap,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
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
        case 3: _t->send_startup(); break;
        case 4: _t->connectionFromClient(); break;
        case 5: _t->clientDisconnected(); break;
        case 6: _t->set_time_mpv((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->pause_mpv(); break;
        case 8: _t->play_mpv(); break;
        case 9: _t->get_file_name(); break;
        case 10: _t->get_duration(); break;
        case 11: _t->get_volume(); break;
        case 12: _t->get_time(); break;
        case 13: _t->setVolume_mpv((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->load_file_mpv((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->send_tree_from_file(); break;
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
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
