/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serveur/mainwindow.h"
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
    QByteArrayData data[29];
    char stringdata0[305];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 9), // "signal_on"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "change_song"
QT_MOC_LITERAL(4, 34, 8), // "signalUI"
QT_MOC_LITERAL(5, 43, 10), // "signalType"
QT_MOC_LITERAL(6, 54, 10), // "closeEvent"
QT_MOC_LITERAL(7, 65, 12), // "send_pressed"
QT_MOC_LITERAL(8, 78, 11), // "search_file"
QT_MOC_LITERAL(9, 90, 11), // "search_list"
QT_MOC_LITERAL(10, 102, 19), // "load_tree_from_file"
QT_MOC_LITERAL(11, 122, 23), // "load_children_from_file"
QT_MOC_LITERAL(12, 146, 12), // "QTextStream*"
QT_MOC_LITERAL(13, 159, 2), // "in"
QT_MOC_LITERAL(14, 162, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(15, 179, 6), // "parent"
QT_MOC_LITERAL(16, 186, 17), // "save_tree_to_file"
QT_MOC_LITERAL(17, 204, 9), // "visitTree"
QT_MOC_LITERAL(18, 214, 12), // "QTreeWidget*"
QT_MOC_LITERAL(19, 227, 4), // "tree"
QT_MOC_LITERAL(20, 232, 12), // "QStringList&"
QT_MOC_LITERAL(21, 245, 4), // "list"
QT_MOC_LITERAL(22, 250, 4), // "item"
QT_MOC_LITERAL(23, 255, 10), // "reset_tree"
QT_MOC_LITERAL(24, 266, 13), // "add_directory"
QT_MOC_LITERAL(25, 280, 5), // "QDir*"
QT_MOC_LITERAL(26, 286, 3), // "dir"
QT_MOC_LITERAL(27, 290, 10), // "print_name"
QT_MOC_LITERAL(28, 301, 3) // "col"

    },
    "MainWindow\0signal_on\0\0change_song\0"
    "signalUI\0signalType\0closeEvent\0"
    "send_pressed\0search_file\0search_list\0"
    "load_tree_from_file\0load_children_from_file\0"
    "QTextStream*\0in\0QTreeWidgetItem*\0"
    "parent\0save_tree_to_file\0visitTree\0"
    "QTreeWidget*\0tree\0QStringList&\0list\0"
    "item\0reset_tree\0add_directory\0QDir*\0"
    "dir\0print_name\0col"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    1,   90,    2, 0x06 /* Public */,
       4,    2,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   98,    2, 0x0a /* Public */,
       7,    0,   99,    2, 0x0a /* Public */,
       8,    0,  100,    2, 0x0a /* Public */,
       9,    0,  101,    2, 0x0a /* Public */,
      10,    0,  102,    2, 0x0a /* Public */,
      11,    2,  103,    2, 0x0a /* Public */,
      16,    0,  108,    2, 0x0a /* Public */,
      17,    1,  109,    2, 0x0a /* Public */,
      17,    2,  112,    2, 0x0a /* Public */,
      23,    0,  117,    2, 0x0a /* Public */,
      24,    2,  118,    2, 0x0a /* Public */,
      27,    2,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QVariantMap,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14,   13,   15,
    QMetaType::Void,
    QMetaType::QStringList, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 14,   21,   22,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25, 0x80000000 | 14,   26,   15,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Int,   22,   28,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_on(); break;
        case 1: _t->change_song((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->signalUI((*reinterpret_cast< signalType(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        case 3: _t->closeEvent(); break;
        case 4: _t->send_pressed(); break;
        case 5: _t->search_file(); break;
        case 6: _t->search_list(); break;
        case 7: _t->load_tree_from_file(); break;
        case 8: _t->load_children_from_file((*reinterpret_cast< QTextStream*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 9: _t->save_tree_to_file(); break;
        case 10: { QStringList _r = _t->visitTree((*reinterpret_cast< QTreeWidget*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 11: _t->visitTree((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 12: _t->reset_tree(); break;
        case 13: _t->add_directory((*reinterpret_cast< QDir*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 14: _t->print_name((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTreeWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::signal_on)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::change_song)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(signalType , QVariantMap );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::signalUI)) {
                *result = 2;
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::signal_on()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MainWindow::change_song(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::signalUI(signalType _t1, QVariantMap _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
