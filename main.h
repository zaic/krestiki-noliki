#pragma once

#include <QtCore/QDebug>
#include <QQuickItem>

class MyClass : public QObject {
    Q_OBJECT

public:
    MyClass() = default;
    ~MyClass() = default;

public slots:
    void cppSlot(const QString& msg) {
       qDebug() << "Called the C++ slot with value:" << msg;

       /*
       QQuickItem *item =
           qobject_cast<QQuickItem*>(v.value<QObject*>());
       qDebug() << "Item dimensions:" << item->width()
                << item->height();
       */
    }
};
