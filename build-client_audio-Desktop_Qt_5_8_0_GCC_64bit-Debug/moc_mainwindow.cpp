/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../client_audio/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "signalToClient"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 10), // "signalType"
QT_MOC_LITERAL(4, 38, 10), // "closeEvent"
QT_MOC_LITERAL(5, 49, 7), // "sl_play"
QT_MOC_LITERAL(6, 57, 8), // "sl_pause"
QT_MOC_LITERAL(7, 66, 9), // "sl_volume"
QT_MOC_LITERAL(8, 76, 16), // "setDisplay_timer"
QT_MOC_LITERAL(9, 93, 19), // "slider_song_pressed"
QT_MOC_LITERAL(10, 113, 20), // "slider_song_released"
QT_MOC_LITERAL(11, 134, 7), // "sl_stop"
QT_MOC_LITERAL(12, 142, 7), // "sl_next"
QT_MOC_LITERAL(13, 150, 7), // "sl_back"
QT_MOC_LITERAL(14, 158, 7), // "sl_mute"
QT_MOC_LITERAL(15, 166, 11), // "sl_lang_fra"
QT_MOC_LITERAL(16, 178, 11), // "sl_lang_eng"
QT_MOC_LITERAL(17, 190, 11), // "sl_lang_ger"
QT_MOC_LITERAL(18, 202, 17), // "messageFromClient"
QT_MOC_LITERAL(19, 220, 25), // "load_children_from_string"
QT_MOC_LITERAL(20, 246, 12), // "QTextStream*"
QT_MOC_LITERAL(21, 259, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(22, 276, 21) // "load_tree_from_string"

    },
    "MainWindow\0signalToClient\0\0signalType\0"
    "closeEvent\0sl_play\0sl_pause\0sl_volume\0"
    "setDisplay_timer\0slider_song_pressed\0"
    "slider_song_released\0sl_stop\0sl_next\0"
    "sl_back\0sl_mute\0sl_lang_fra\0sl_lang_eng\0"
    "sl_lang_ger\0messageFromClient\0"
    "load_children_from_string\0QTextStream*\0"
    "QTreeWidgetItem*\0load_tree_from_string"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  109,    2, 0x0a /* Public */,
       5,    0,  110,    2, 0x0a /* Public */,
       6,    0,  111,    2, 0x0a /* Public */,
       7,    1,  112,    2, 0x0a /* Public */,
       8,    0,  115,    2, 0x0a /* Public */,
       9,    0,  116,    2, 0x0a /* Public */,
      10,    0,  117,    2, 0x0a /* Public */,
      11,    0,  118,    2, 0x0a /* Public */,
      12,    0,  119,    2, 0x0a /* Public */,
      13,    0,  120,    2, 0x0a /* Public */,
      14,    0,  121,    2, 0x0a /* Public */,
      15,    0,  122,    2, 0x0a /* Public */,
      16,    0,  123,    2, 0x0a /* Public */,
      17,    0,  124,    2, 0x0a /* Public */,
      18,    2,  125,    2, 0x0a /* Public */,
      19,    2,  130,    2, 0x0a /* Public */,
      22,    1,  135,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QVariantMap,    2,    2,

 // slots: parameters
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QVariantMap,    2,    2,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 21,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalToClient((*reinterpret_cast< signalType(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        case 1: _t->closeEvent(); break;
        case 2: _t->sl_play(); break;
        case 3: _t->sl_pause(); break;
        case 4: _t->sl_volume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setDisplay_timer(); break;
        case 6: _t->slider_song_pressed(); break;
        case 7: _t->slider_song_released(); break;
        case 8: _t->sl_stop(); break;
        case 9: _t->sl_next(); break;
        case 10: _t->sl_back(); break;
        case 11: _t->sl_mute(); break;
        case 12: _t->sl_lang_fra(); break;
        case 13: _t->sl_lang_eng(); break;
        case 14: _t->sl_lang_ger(); break;
        case 15: _t->messageFromClient((*reinterpret_cast< signalType(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        case 16: _t->load_children_from_string((*reinterpret_cast< QTextStream*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 17: _t->load_tree_from_string((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(signalType , QVariantMap );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::signalToClient)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::signalToClient(signalType _t1, QVariantMap _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
