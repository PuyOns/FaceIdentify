/****************************************************************************
** Meta object code from reading C++ file 'functiondisplaywindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../functiondisplaywindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'functiondisplaywindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FunctionDisplayWindow_t {
    QByteArrayData data[9];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FunctionDisplayWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FunctionDisplayWindow_t qt_meta_stringdata_FunctionDisplayWindow = {
    {
QT_MOC_LITERAL(0, 0, 21), // "FunctionDisplayWindow"
QT_MOC_LITERAL(1, 22, 18), // "sendStartRecording"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 17), // "sendStopRecording"
QT_MOC_LITERAL(4, 60, 17), // "sendEdgeDetection"
QT_MOC_LITERAL(5, 78, 14), // "sendPhotograph"
QT_MOC_LITERAL(6, 93, 29), // "myChangeFunctionDisplayWindow"
QT_MOC_LITERAL(7, 123, 3), // "val"
QT_MOC_LITERAL(8, 127, 20) // "ReceiveCompareResult"

    },
    "FunctionDisplayWindow\0sendStartRecording\0"
    "\0sendStopRecording\0sendEdgeDetection\0"
    "sendPhotograph\0myChangeFunctionDisplayWindow\0"
    "val\0ReceiveCompareResult"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FunctionDisplayWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   48,    2, 0x0a /* Public */,
       8,    2,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Double, QMetaType::Int,    2,    2,

       0        // eod
};

void FunctionDisplayWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FunctionDisplayWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendStartRecording(); break;
        case 1: _t->sendStopRecording(); break;
        case 2: _t->sendEdgeDetection(); break;
        case 3: _t->sendPhotograph(); break;
        case 4: _t->myChangeFunctionDisplayWindow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->ReceiveCompareResult((*reinterpret_cast< const double(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FunctionDisplayWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FunctionDisplayWindow::sendStartRecording)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FunctionDisplayWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FunctionDisplayWindow::sendStopRecording)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FunctionDisplayWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FunctionDisplayWindow::sendEdgeDetection)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FunctionDisplayWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FunctionDisplayWindow::sendPhotograph)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FunctionDisplayWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_FunctionDisplayWindow.data,
    qt_meta_data_FunctionDisplayWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FunctionDisplayWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FunctionDisplayWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FunctionDisplayWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FunctionDisplayWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void FunctionDisplayWindow::sendStartRecording()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FunctionDisplayWindow::sendStopRecording()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FunctionDisplayWindow::sendEdgeDetection()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void FunctionDisplayWindow::sendPhotograph()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
