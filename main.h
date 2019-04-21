#pragma once

#include <QtCore/QDebug>
#include <QQuickItem>

class MyClass : public QObject {
    Q_OBJECT

public:
    MyClass(QObject& rootObject): m_rootObject(rootObject) {}

public slots:
    void cppSlot(const QString& msg);

private:
    QObject& m_rootObject;
};
