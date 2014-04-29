/****************************************************************************
** Meta object code from reading C++ file 'guimain.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "guimain.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guimain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_guimain_t {
    QByteArrayData data[14];
    char stringdata[231];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_guimain_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_guimain_t qt_meta_stringdata_guimain = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 20),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 13),
QT_MOC_LITERAL(4, 44, 13),
QT_MOC_LITERAL(5, 58, 21),
QT_MOC_LITERAL(6, 80, 20),
QT_MOC_LITERAL(7, 101, 15),
QT_MOC_LITERAL(8, 117, 27),
QT_MOC_LITERAL(9, 145, 3),
QT_MOC_LITERAL(10, 149, 6),
QT_MOC_LITERAL(11, 156, 35),
QT_MOC_LITERAL(12, 192, 5),
QT_MOC_LITERAL(13, 198, 31)
    },
    "guimain\0on_Runbutton_clicked\0\0"
    "on_fs_clicked\0on_s4_clicked\0"
    "on_singlemode_clicked\0on_rangemode_clicked\0"
    "on_Save_clicked\0on_Resultstable_cellClicked\0"
    "row\0column\0on_materialname_currentIndexChanged\0"
    "index\0on_pipename_currentIndexChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_guimain[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08,
       3,    0,   60,    2, 0x08,
       4,    0,   61,    2, 0x08,
       5,    0,   62,    2, 0x08,
       6,    0,   63,    2, 0x08,
       7,    0,   64,    2, 0x08,
       8,    2,   65,    2, 0x08,
      11,    1,   70,    2, 0x08,
      13,    1,   73,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void guimain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        guimain *_t = static_cast<guimain *>(_o);
        switch (_id) {
        case 0: _t->on_Runbutton_clicked(); break;
        case 1: _t->on_fs_clicked(); break;
        case 2: _t->on_s4_clicked(); break;
        case 3: _t->on_singlemode_clicked(); break;
        case 4: _t->on_rangemode_clicked(); break;
        case 5: _t->on_Save_clicked(); break;
        case 6: _t->on_Resultstable_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->on_materialname_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_pipename_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject guimain::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_guimain.data,
      qt_meta_data_guimain,  qt_static_metacall, 0, 0}
};


const QMetaObject *guimain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *guimain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_guimain.stringdata))
        return static_cast<void*>(const_cast< guimain*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int guimain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
