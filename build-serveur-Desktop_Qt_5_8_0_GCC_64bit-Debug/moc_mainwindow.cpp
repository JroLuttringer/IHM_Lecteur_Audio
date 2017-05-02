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
    QByteArrayData data[26];
    char stringdata0[274];
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
QT_MOC_LITERAL(4, 34, 12), // "send_pressed"
QT_MOC_LITERAL(5, 47, 11), // "search_file"
QT_MOC_LITERAL(6, 59, 11), // "search_list"
QT_MOC_LITERAL(7, 71, 19), // "load_tree_from_file"
QT_MOC_LITERAL(8, 91, 23), // "load_children_from_file"
QT_MOC_LITERAL(9, 115, 12), // "QTextStream*"
QT_MOC_LITERAL(10, 128, 2), // "in"
QT_MOC_LITERAL(11, 131, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(12, 148, 6), // "parent"
QT_MOC_LITERAL(13, 155, 17), // "save_tree_to_file"
QT_MOC_LITERAL(14, 173, 9), // "visitTree"
QT_MOC_LITERAL(15, 183, 12), // "QTreeWidget*"
QT_MOC_LITERAL(16, 196, 4), // "tree"
QT_MOC_LITERAL(17, 201, 12), // "QStringList&"
QT_MOC_LITERAL(18, 214, 4), // "list"
QT_MOC_LITERAL(19, 219, 4), // "item"
QT_MOC_LITERAL(20, 224, 10), // "reset_tree"
QT_MOC_LITERAL(21, 235, 13), // "add_directory"
QT_MOC_LITERAL(22, 249, 5), // "QDir*"
QT_MOC_LITERAL(23, 255, 3), // "dir"
QT_MOC_LITERAL(24, 259, 10), // "print_name"
QT_MOC_LITERAL(25, 270, 3) // "col"

    },
    "MainWindow\0signal_on\0\0change_song\0"
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
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    1,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   83,    2, 0x0a /* Public */,
       5,    0,   84,    2, 0x0a /* Public */,
       6,    0,   85,    2, 0x0a /* Public */,
       7,    0,   86,    2, 0x0a /* Public */,
       8,    2,   87,    2, 0x0a /* Public */,
      13,    0,   92,    2, 0x0a /* Public */,
      14,    1,   93,    2, 0x0a /* Public */,
      14,    2,   96,    2, 0x0a /* Public */,
      20,    0,  101,    2, 0x0a /* Public */,
      21,    2,  102,    2, 0x0a /* Public */,
      24,    2,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11,   10,   12,
    QMetaType::Void,
    QMetaType::QStringList, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 17, 0x80000000 | 11,   18,   19,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 11,   23,   12,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int,   19,   25,

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
        case 2: _t->send_pressed(); break;
        case 3: _t->search_file(); break;
        case 4: _t->search_list(); break;
        case 5: _t->load_tree_from_file(); break;
        case 6: _t->load_children_from_file((*reinterpret_cast< QTextStream*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 7: _t->save_tree_to_file(); break;
        case 8: { QStringList _r = _t->visitTree((*reinterpret_cast< QTreeWidget*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 9: _t->visitTree((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 10: _t->reset_tree(); break;
        case 11: _t->add_directory((*reinterpret_cast< QDir*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 12: _t->print_name((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
