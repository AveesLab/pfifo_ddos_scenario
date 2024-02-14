/****************************************************************************
** Meta object code from reading C++ file 'WeatherAPI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "WeatherAPI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WeatherAPI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WeatherAPI_t {
    QByteArrayData data[10];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WeatherAPI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WeatherAPI_t qt_meta_stringdata_WeatherAPI = {
    {
QT_MOC_LITERAL(0, 0, 10), // "WeatherAPI"
QT_MOC_LITERAL(1, 11, 14), // "weatherUpdated"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 21), // "onWeatherDataReceived"
QT_MOC_LITERAL(4, 49, 14), // "QNetworkReply*"
QT_MOC_LITERAL(5, 64, 5), // "reply"
QT_MOC_LITERAL(6, 70, 14), // "requestWeather"
QT_MOC_LITERAL(7, 85, 4), // "city"
QT_MOC_LITERAL(8, 90, 11), // "weatherIcon"
QT_MOC_LITERAL(9, 102, 11) // "temperature"

    },
    "WeatherAPI\0weatherUpdated\0\0"
    "onWeatherDataReceived\0QNetworkReply*\0"
    "reply\0requestWeather\0city\0weatherIcon\0"
    "temperature"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WeatherAPI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       2,   36, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   30,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
       6,    1,   33,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    7,

 // properties: name, type, flags
       8, QMetaType::QString, 0x00495001,
       9, QMetaType::QString, 0x00495001,

 // properties: notify_signal_id
       0,
       0,

       0        // eod
};

void WeatherAPI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WeatherAPI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->weatherUpdated(); break;
        case 1: _t->onWeatherDataReceived((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->requestWeather((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WeatherAPI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WeatherAPI::weatherUpdated)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<WeatherAPI *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->weatherIcon(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->temperature(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject WeatherAPI::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_WeatherAPI.data,
    qt_meta_data_WeatherAPI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WeatherAPI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WeatherAPI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WeatherAPI.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WeatherAPI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WeatherAPI::weatherUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
