/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13EncryptWorkerE_t {};
} // unnamed namespace

template <> constexpr inline auto EncryptWorker::qt_create_metaobjectdata<qt_meta_tag_ZN13EncryptWorkerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "EncryptWorker",
        "finished",
        "",
        "ProcessMetrics",
        "metrics",
        "error",
        "err",
        "progressUpdate",
        "percentage",
        "status",
        "process"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'finished'
        QtMocHelpers::SignalData<void(const ProcessMetrics &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'error'
        QtMocHelpers::SignalData<void(QString)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'progressUpdate'
        QtMocHelpers::SignalData<void(int, QString)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 8 }, { QMetaType::QString, 9 },
        }}),
        // Slot 'process'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<EncryptWorker, qt_meta_tag_ZN13EncryptWorkerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject EncryptWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13EncryptWorkerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13EncryptWorkerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13EncryptWorkerE_t>.metaTypes,
    nullptr
} };

void EncryptWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<EncryptWorker *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->finished((*reinterpret_cast< std::add_pointer_t<ProcessMetrics>>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->progressUpdate((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->process(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (EncryptWorker::*)(const ProcessMetrics & )>(_a, &EncryptWorker::finished, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (EncryptWorker::*)(QString )>(_a, &EncryptWorker::error, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (EncryptWorker::*)(int , QString )>(_a, &EncryptWorker::progressUpdate, 2))
            return;
    }
}

const QMetaObject *EncryptWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EncryptWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13EncryptWorkerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EncryptWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void EncryptWorker::finished(const ProcessMetrics & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void EncryptWorker::error(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void EncryptWorker::progressUpdate(int _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}
namespace {
struct qt_meta_tag_ZN13DecryptWorkerE_t {};
} // unnamed namespace

template <> constexpr inline auto DecryptWorker::qt_create_metaobjectdata<qt_meta_tag_ZN13DecryptWorkerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DecryptWorker",
        "finished",
        "",
        "ProcessMetrics",
        "metrics",
        "error",
        "err",
        "progressUpdate",
        "percentage",
        "status",
        "process"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'finished'
        QtMocHelpers::SignalData<void(const ProcessMetrics &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'error'
        QtMocHelpers::SignalData<void(QString)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'progressUpdate'
        QtMocHelpers::SignalData<void(int, QString)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 8 }, { QMetaType::QString, 9 },
        }}),
        // Slot 'process'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DecryptWorker, qt_meta_tag_ZN13DecryptWorkerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DecryptWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13DecryptWorkerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13DecryptWorkerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13DecryptWorkerE_t>.metaTypes,
    nullptr
} };

void DecryptWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DecryptWorker *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->finished((*reinterpret_cast< std::add_pointer_t<ProcessMetrics>>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->progressUpdate((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->process(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DecryptWorker::*)(const ProcessMetrics & )>(_a, &DecryptWorker::finished, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DecryptWorker::*)(QString )>(_a, &DecryptWorker::error, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (DecryptWorker::*)(int , QString )>(_a, &DecryptWorker::progressUpdate, 2))
            return;
    }
}

const QMetaObject *DecryptWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DecryptWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13DecryptWorkerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DecryptWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DecryptWorker::finished(const ProcessMetrics & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void DecryptWorker::error(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void DecryptWorker::progressUpdate(int _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "on_pushButton_selectFolder_clicked",
        "",
        "on_pushButton_3_clicked",
        "on_pushButton_save_clicked",
        "on_pushButton_cancel_clicked",
        "on_pushButton_5_clicked",
        "on_pushButton_6_clicked",
        "on_tabWidget_currentChanged",
        "index",
        "on_lineEdit_file_textChanged",
        "text",
        "onEncryptFinished",
        "ProcessMetrics",
        "metrics",
        "onDecryptFinished",
        "onProcessError",
        "error",
        "onProgressUpdate",
        "percentage",
        "status"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_pushButton_selectFolder_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_3_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_save_clicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_cancel_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_5_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_6_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_tabWidget_currentChanged'
        QtMocHelpers::SlotData<void(int)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Slot 'on_lineEdit_file_textChanged'
        QtMocHelpers::SlotData<void(const QString &)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Slot 'onEncryptFinished'
        QtMocHelpers::SlotData<void(const ProcessMetrics &)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 13, 14 },
        }}),
        // Slot 'onDecryptFinished'
        QtMocHelpers::SlotData<void(const ProcessMetrics &)>(15, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 13, 14 },
        }}),
        // Slot 'onProcessError'
        QtMocHelpers::SlotData<void(const QString &)>(16, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 17 },
        }}),
        // Slot 'onProgressUpdate'
        QtMocHelpers::SlotData<void(int, const QString &)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 19 }, { QMetaType::QString, 20 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_pushButton_selectFolder_clicked(); break;
        case 1: _t->on_pushButton_3_clicked(); break;
        case 2: _t->on_pushButton_save_clicked(); break;
        case 3: _t->on_pushButton_cancel_clicked(); break;
        case 4: _t->on_pushButton_5_clicked(); break;
        case 5: _t->on_pushButton_6_clicked(); break;
        case 6: _t->on_tabWidget_currentChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->on_lineEdit_file_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->onEncryptFinished((*reinterpret_cast< std::add_pointer_t<ProcessMetrics>>(_a[1]))); break;
        case 9: _t->onDecryptFinished((*reinterpret_cast< std::add_pointer_t<ProcessMetrics>>(_a[1]))); break;
        case 10: _t->onProcessError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->onProgressUpdate((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
